/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:31 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/12 12:29:08 by abentaye         ###   ########.fr       */
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

int init_mlx(t_base *base)
{
    base->mlx = malloc(sizeof(t_mlx));
    if (!base->mlx)
        return (error_handler("Error"), 1);
    base->mlx->ptr = mlx_init();
    if (!base->mlx->ptr)
        return (error_handler("Error"), 1);
    base->mlx->win = mlx_new_window(base->mlx->ptr, WIDTH, HEIGHT, "cub3D");
    if (!base->mlx->win)
        return (error_handler("Error"), 1);
    base->data->img = mlx_new_image(base->mlx->ptr, WIDTH, HEIGHT);
    if (!base->data->img)
        return (error_handler("Error"), 1);
    base->data->addr = mlx_get_data_addr(base->data->img, &base->data->bits_per_pixel, &base->data->line_length, &base->data->endian);
    if (!base->data->addr)
        return (error_handler("Error"), 1);
    return (0);
}

static void display_text(t_textures *text)
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

void    print_map(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        printf("%s", map[i]);
        i++;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    t_base *base;

    base = malloc(sizeof(t_base));
    if (!base)
        return (error_handler("Error"), 1);
    initialization(base, argv);
    if (!base->data || !base->mlx)
		return(error_handler("Error"), free(base), 1);
    args_suffix_checker(argc, argv);
    if (read_map_file(base) == NULL)
        return (free(base), 1);
    display_text(base->text);
    if (!base->data->map)
        return (free(base->data), free(base->mlx), free(base), 1);
    // print_map(base->data->map);
    return (0);
}
