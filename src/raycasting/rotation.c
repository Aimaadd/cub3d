/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:48:38 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/17 14:34:39 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_vectors(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle) - player->plane_y
		* sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

void	rotate_right(t_base *base)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = base->player->dir_x;
	base->player->dir_x = base->player->dir_x * cos(-base->player->rot_speed)
		- base->player->dir_y * sin(-base->player->rot_speed);
	base->player->dir_y = old_dir_x * sin(-base->player->rot_speed)
		+ base->player->dir_y * cos(-base->player->rot_speed);
	old_plane_x = base->player->plane_x;
	base->player->plane_x = base->player->plane_x
		* cos(-base->player->rot_speed) - base->player->plane_y
		* sin(-base->player->rot_speed);
	base->player->plane_y = old_plane_x * sin(-base->player->rot_speed)
		+ base->player->plane_y * cos(-base->player->rot_speed);
}

void	rotate_left(t_base *base)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = base->player->dir_x;
	base->player->dir_x = base->player->dir_x * cos(base->player->rot_speed)
		- base->player->dir_y * sin(base->player->rot_speed);
	base->player->dir_y = old_dir_x * sin(base->player->rot_speed)
		+ base->player->dir_y * cos(base->player->rot_speed);
	old_plane_x = base->player->plane_x;
	base->player->plane_x = base->player->plane_x * cos(base->player->rot_speed)
		- base->player->plane_y * sin(base->player->rot_speed);
	base->player->plane_y = old_plane_x * sin(base->player->rot_speed)
		+ base->player->plane_y * cos(base->player->rot_speed);
}
