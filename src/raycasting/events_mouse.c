/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:03:19 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/02 15:03:21 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_close(t_base *base)
{
	clean_exit(base);
	return (0);
}

int	handle_mouse_move(int x, int y, t_base *base)
{
	static int	last_x = WIDTH / 2;
	int			delta_x;
	double		rot_speed;

	(void)y;
	delta_x = x - last_x;
	rot_speed = delta_x * 0.002;
	rotate_vectors(base->player, rot_speed);
	last_x = x;
	mlx_clear_window(base->mlx->ptr, base->mlx->win);
	raycasting(base);
	return (0);
}

int	handle_resize(int width, int height, t_base *base)
{
	base->mlx->width = width;
	base->mlx->height = height;
	if (base->data->img)
		mlx_destroy_image(base->mlx->ptr, base->data->img);
	base->data->img = mlx_new_image(base->mlx->ptr, width, height);
	if (!base->data->img)
		return (error_handler("Error: Failed to create new image"), 1);
	base->data->addr = mlx_get_data_addr(base->data->img, \
		&base->data->bits_per_pixel, &base->data->line_length, \
		&base->data->endian);
	raycasting(base);
	return (0);
} 