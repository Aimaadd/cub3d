/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:35:18 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/02 14:56:39 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <mlx.h>

static int	init_base_data(t_base *base)
{
	base->data = malloc(sizeof(t_data));
	if (!base->data)
		return (1);
	base->data->addr = NULL;
	base->data->bits_per_pixel = 0;
	base->data->endian = 0;
	base->data->img = NULL;
	base->data->line_length = 0;
	base->data->map = NULL;
	return (0);
}

static int	init_text(t_base *base)
{
	base->text = malloc(sizeof(t_textures));
	if (!base->text)
		return (1);
	base->text->C = NULL;
	base->text->EA = NULL;
	base->text->F = NULL;
	base->text->NO = NULL;
	base->text->SO = NULL;
	base->text->WE = NULL;
	base->text->set = 0;
	return (0);
}

static int	init_player(t_base *base)
{
	base->player = malloc(sizeof(t_player));
	if (!base->player)
		return (1);
	base->player->dir = 0;
	base->player->pos_x = 0;
	base->player->pos_y = 0;
	return (0);
}

static int	init_map(t_base *base)
{
	base->map = malloc(sizeof(t_map));
	if (!base->map)
		return (1);
	base->map->character = 0;
	base->map->closed = 0;
	base->map->invalid = 0;
	return (0);
}

void	initialization(t_base *base, char **argv)
{
	base->map_name = argv[1];
	if (init_player(base) == 1)
		error_handler("Error");
	if (init_map(base) == 1)
	{
		free(base->player);
		error_handler("Error");
	}
	if (init_base_data(base) == 1)
		error_handler("Error");
	if (!base->data)
	{
		free(base);
		error_handler("Error");
	}
	if (init_text(base) == 1)
	{
		free(base->data);
		free(base);
		error_handler("Error");
	}
	if (init_mlx(base) == 1)
	{
		free(base->text);
		free(base->data);
		free(base);
		error_handler("Error");
	}
}
