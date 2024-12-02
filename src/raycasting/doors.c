/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:03:27 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/02 15:03:29 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	toggle_door(t_base *base)
{
	int	check_x;
	int	check_y;

	check_x = (int)(base->player->pos_x + base->player->dir_x);
	check_y = (int)(base->player->pos_y + base->player->dir_y);
	if (base->data->map[check_x][check_y] == 'D')
		base->data->map[check_x][check_y] = 'O';
	else if (base->data->map[check_x][check_y] == 'O')
		base->data->map[check_x][check_y] = 'D';
}

int	is_door(char c)
{
	return (c == 'D' || c == 'O');
} 