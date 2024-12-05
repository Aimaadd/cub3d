/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:01:13 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/05 16:05:20 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	get_wall_color(t_base *base, t_ray_calc *rc)
{
	int	color;

	color = 0xFF0000;
	if (base->data->map[rc->map_x][rc->map_y] == 'D')
		color = 0x808080;
	else if (base->data->map[rc->map_x][rc->map_y] == 'O')
		color = 0x404040;
	if (rc->side == 1)
		color = color / 2;
	return (color);
}

void	raycasting(t_base *base)
{
	t_ray_calc	rc;
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray_dir(base, &rc, x);
		calc_step_dist(&rc, base->player);
		perform_dda(&rc, base);
		calc_wall_height(&rc);
		draw_vertical_line(base->data, x, rc.draw_start, \
			rc.draw_end, get_wall_color(base, &rc));
		x++;
	}
	mlx_put_image_to_window(base->mlx->ptr, base->mlx->win, \
		base->data->img, 0, 0);
} 