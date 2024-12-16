/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:31 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/16 15:33:55 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	args_suffix_checker(int argc, char **argv)
{
	if (argc != 2)
		return (write(1, "Error\n", 6), 1);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		return (write(1, "Error\n", 6), exit(1), 1);
	return (0);
}

int	init_mlx(t_base *base)
{
	base->mlx = malloc(sizeof(t_mlx));
	if (!base->mlx)
		return (free_all(base), 1);
	base->mlx->ptr = mlx_init();
	if (!base->mlx->ptr)
		return (free_all(base), 1);
	base->mlx->win = mlx_new_window(base->mlx->ptr, WIDTH, HEIGHT, "cub3D");
	if (!base->mlx->win)
		return (free_all(base), 1);
	base->data->img = mlx_new_image(base->mlx->ptr, WIDTH, HEIGHT);
	if (!base->data->img)
		return (free_all(base), 1);
	base->data->addr = mlx_get_data_addr(base->data->img,
			&base->data->bits_per_pixel, &base->data->line_length,
			&base->data->endian);
	if (!base->data->addr)
		return (free_all(base), 1);
	return (0);
}

static void	display_text(t_textures *text)
{
	printf("DISPLAY TEXTURES\n");
	printf("NO : %s\n", text->NO);
	printf("SO : %s\n", text->SO);
	printf("WE :%s\n", text->WE);
	printf("EA :%s\n", text->EA);
	printf("F : %s\n", text->F);
	printf("C : %s\n", text->C);
	printf("set : %d\n", text->set);
	printf("DONE PRINTING\n");
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	printf ("\nPRINTING MAP\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_base	*base;
	pid_t	pid;

	
	base = malloc(sizeof(t_base));
	if (!base)
		return (free_all(base), 1);
	initialization(base, argv);
	if (!base->data || !base->mlx)
		return (free_all(base), 1);
	args_suffix_checker(argc, argv);
	if (read_map_file(base) == NULL)
		return (free_all(base), 1);
	display_text(base->text);
	print_map(base->data->map);
	if (!base->data->map)
		return (free_all(base), 1);
	if (init_textures_and_mlx(base) == 1)
		return (1);
	pid = fork();
	if (pid == 0)
		play_music();
	game_loop(base);
	if (pid > 0)
        kill(pid, SIGTERM);
	return (0);
}
