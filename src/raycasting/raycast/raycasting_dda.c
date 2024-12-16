/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:01:00 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/05 15:58:56 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	perform_dda(t_ray_calc *rc, t_base *base)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (base->data->map[rc->map_x][rc->map_y] == '1')
			rc->hit = 1;
	}
}

void	calc_wall_height(t_ray_calc *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
	if (rc->perp_wall_dist <= 0)
		rc->perp_wall_dist = 0.1;
	rc->line_height = (int)(HEIGHT / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + HEIGHT / 2;
	if (rc->draw_end >= HEIGHT)
		rc->draw_end = HEIGHT - 1;
} 