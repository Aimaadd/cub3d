/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:00:02 by pepi              #+#    #+#             */
/*   Updated: 2024/12/16 15:11:52 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
} 

int init_textures_and_mlx(t_base *base) {
    // Initialisation de MLX
    if (init_mlx(base) != 0) {
        printf("Erreur d'initialisation MLX\n");
        return (1);
        free_all(base);
    }
    
    // Chargement des textures
    if (load_textures(base) != 0) {
        printf("Erreur de chargement des textures\n");
        return (1);
        free_all(base);
    }
    
    // Vérification des dimensions
    if (verify_texture_dimensions(base) != 0) {
        return (1);
        free_all(base);
    }
    
    return (0);
}