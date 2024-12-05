/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:05:49 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/05 16:05:26 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	init_player_dir_ns(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->dir == 'S')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

static void	init_player_dir_ew(t_player *player)
{
	if (player->dir == 'E')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->dir == 'W')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

void	init_player_direction(t_player *player)
{
	init_player_dir_ns(player);
	init_player_dir_ew(player);
	player->move_speed = 0.05;
	player->rot_speed = 0.05;
}

void	draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	int		y;
	char	*dst;

	y = 0;
	while (y < start)
	{
		dst = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *)dst = 0x87CEEB;
		y++;
	}
	while (y < end)
	{
		dst = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
		y++;
	}
	while (y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *)dst = 0x808080;
		y++;
	}
}
