/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:35:18 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/15 17:18:00 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static int	mlx_setup(t_mlx **mlx)
{
	*mlx = malloc(sizeof(t_mlx));
	if (!*mlx)
		return (1);
	(*mlx)->ptr = mlx_init();
	if (!(*mlx)->ptr)
		return (1);
	(*mlx)->win = mlx_new_window((*mlx)->ptr, WIDTH, HEIGHT, "cub3D");
	if (!(*mlx)->win)
		return (1);
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

static int	init_player(t_player *player)
{
	if (!player)
		return (1);
	player->dir = 0;
	player->pos_x = 0;
	player->pos_y = 0;
	return (0);
}

void	initialization(t_base *base, char **argv)
{
	base->map_name = argv[1];
	base->player = malloc(sizeof(t_player));
	if (init_player(base->player) == 1)
		error_handler("Allocation failed");
	if (init_base_data(base) == 1)
		error_handler("Allocation failed");
	if (!base->data)
	{
		free(base);
		error_handler("Allocation error");
	}
	if (init_text(base) == 1)
	{
		free(base->data);
		free(base);
		error_handler("Allocation failed");
	}
	if (mlx_setup(&base->mlx) == 1)
	{
		free(base->text);
		free(base->data);
		free(base);
		error_handler("MLX setup failed");
	}
}
