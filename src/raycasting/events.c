/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:48:12 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/16 14:35:17 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void clean_exit(t_base *base)
{
    // Arrêter tous les processus enfants (y compris la musique)
    kill(0, SIGTERM);
    
    if (base->mlx->win)
        mlx_destroy_window(base->mlx->ptr, base->mlx->win);
    if (base->data->img)
        mlx_destroy_image(base->mlx->ptr, base->data->img);
    free(base->mlx);
    free(base->data);
    free(base->player);
    free(base->map);
    free(base->text);
    free(base);
    exit(0);
}

int handle_keypress(int keycode, t_base *base)
{
    if (keycode == 13 || keycode == 119)      // W
        move_forward(base);
    else if (keycode == 1 || keycode == 115)  // S
        move_backward(base);
    else if (keycode == 0 || keycode == 97)   // A
        move_left(base);
    else if (keycode == 2 || keycode == 100)  // D
        move_right(base);
    else if (keycode == 124)                  // Flèche droite
        rotate_left(base);
    else if (keycode == 123)                  // Flèche gauche
        rotate_right(base);
    else if (keycode == 53)                   // ESC
        clean_exit(base);
    mlx_clear_window(base->mlx->ptr, base->mlx->win);
    raycasting(base);
    return (0);
}

int handle_close(t_base *base)
{
    clean_exit(base);
    return (0);
}

int handle_mouse_move(int x, int y, t_base *base)
{
	(void)y;
    static int last_x = WIDTH / 2;  // Position initiale de la souris au centre

    // Calculer la différence de position de la souris
    int delta_x = x - last_x;

    double rot_speed = delta_x * 0.002;  // sensibilité
    double old_dir_x = base->player->dir_x;
    base->player->dir_x = base->player->dir_x * cos(rot_speed) - base->player->dir_y * sin(rot_speed);
    base->player->dir_y = old_dir_x * sin(rot_speed) + base->player->dir_y * cos(rot_speed);

    double old_plane_x = base->player->plane_x;
    base->player->plane_x = base->player->plane_x * cos(rot_speed) - base->player->plane_y * sin(rot_speed);
    base->player->plane_y = old_plane_x * sin(rot_speed) + base->player->plane_y * cos(rot_speed);

    last_x = x;

    mlx_clear_window(base->mlx->ptr, base->mlx->win);
    raycasting(base);

    return (0);
}

int handle_resize(int width, int height, t_base *base)
{
    base->mlx->width = width;
    base->mlx->height = height;
    
    if (base->data->img)
        mlx_destroy_image(base->mlx->ptr, base->data->img);
    base->data->img = mlx_new_image(base->mlx->ptr, width, height);
    if (!base->data->img)
        return (printf("Error: Failed to create new image"), 1);
    base->data->addr = mlx_get_data_addr(base->data->img, 
        &base->data->bits_per_pixel, 
        &base->data->line_length, 
        &base->data->endian);
    raycasting(base);
    return (0);
}

