/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:31 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/02 13:50:25 by rpepi            ###   ########.fr       */
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
    printf("Image info: bpp=%d, line_length=%d, endian=%d\n",
           base->data->bits_per_pixel,
           base->data->line_length,
           base->data->endian);
    return (0);
}

void    print_map(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    t_base *base;
    char *test_map[] = {
        "111111111",
        "100000001",
        "100N00001",
        "100000001",
        "111111111",
        NULL
    };
    (void)argc;
    (void)argv;
    base = malloc(sizeof(t_base));
    if (!base)
        return (error_handler("Error"), 1);
    initialization(base, argv);
    if (!base->data || !base->mlx)
        return(error_handler("Error"), free(base), 1);
    
    // Utiliser la map de test
    base->data->map = test_map;
    if (valid_map(base) == 1)
        return (printf("Map invalide\n"), 1);
    
    // Afficher la map et les informations du joueur
    print_map(base->data->map);
    printf("Position joueur: x=%f, y=%f, dir=%c\n", 
           base->player->pos_x, 
           base->player->pos_y, 
           base->player->dir);
    game_loop(base);
    // Libération de la mémoire
    free(base->mlx);
    free(base->data);
    free(base->player);
    free(base->map);
    free(base->text);
    free(base);
    return (0);
}
