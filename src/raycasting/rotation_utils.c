/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:42 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/02 15:02:44 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rotate_vectors(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - \
		player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + \
		player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle) - \
		player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + \
		player->plane_y * cos(angle);
}

void	rotate_right(t_base *base)
{
	rotate_vectors(base->player, -base->player->rot_speed);
}

void	rotate_left(t_base *base)
{
	rotate_vectors(base->player, base->player->rot_speed);
} 