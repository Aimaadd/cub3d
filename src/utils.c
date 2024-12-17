/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:00:02 by pepi              #+#    #+#             */
/*   Updated: 2024/12/17 16:58:50 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

int	init_textures_and_mlx(t_base *base)
{
	if (init_mlx(base) != 0)
	{
		free_all(base, "Bad texture");
		return (1);
	}
	if (load_textures(base) != 0)
	{
		free_all(base, "Bad texture");
		return (1);
	}
	if (verify_texture_dimensions(base) != 0)
	{
		free_all(base, "bad texture");
		return (1);
	}
	return (0);
}

int	normalize_color_value(int value)
{
	if (value > 255)
		value = 255;
	if (value < 0)
		value = 0;
	return (value);
}
