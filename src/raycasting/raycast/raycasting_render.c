/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:01:13 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/17 15:07:08 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

unsigned int	create_rgb(char *color)
{
	char			**split;
	int				r;
	int				g;
	int				b;
	unsigned int	rgb;

	if (!color)
		return (0xFF000000);
	split = ft_split(color, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		if (split)
			ft_free_split(split);
		return (0xFF000000);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	r = (r > 255) ? 255 : r; // si supérieur à 255, on met 255
	g = (g > 255) ? 255 : g;
	b = (b > 255) ? 255 : b;
	r = (r < 0) ? 0 : r; // si inférieur à 0, on met 0
	g = (g < 0) ? 0 : g;
	b = (b < 0) ? 0 : b;
	rgb = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
		// on met les valeurs dans rgb
	ft_free_split(split);
	return (rgb);
}

void	raycasting(t_base *base)
{
	t_ray_calc	rc;
	int			x;

	// Dessiner le fond avant le raycasting
	draw_background(base);
	x = 0;
	while (x < WIDTH)
	{
		init_ray_dir(base, &rc, x);
		calc_step_dist(&rc, base->player);
		perform_dda(&rc, base);
		calc_wall_height(&rc);
		render_wall(base, &rc, x);
		x++;
	}
	mlx_put_image_to_window(base->mlx->ptr, base->mlx->win, base->data->img, 0,
		0);
}

void	render_wall(t_base *base, t_ray_calc *rc, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	double	tex_pos;

	// Calculer la hauteur de la ligne à dessiner
	line_height = (int)(HEIGHT / rc->perp_wall_dist);
	// Calculer les points de début et de fin de la ligne verticale
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	// Calculer la position x exacte de la texture
	if (rc->side == 0)
		wall_x = base->player->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		wall_x = base->player->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	wall_x -= floor(wall_x);
	// Coordonnée x de la texture
	int tex_x = (int)(wall_x * 64.0); // 64 est la largeur fixe de la texture
	if (rc->side == 0 && rc->ray_dir_x > 0)
		tex_x = 64 - tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		tex_x = 64 - tex_x - 1;
	// Pour chaque pixel vertical de la ligne
	double step = 64.0 / line_height; // 64 est la hauteur fixe de la texture
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	for (int y = draw_start; y < draw_end; y++)
	{
		int tex_y = (int)tex_pos & 63;
			// 63 = 64-1 (masque pour rester dans les limites)
		tex_pos += step;
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			my_mlx_pixel_put(base->data, x, y,
				get_texture_color(&base->textures[rc->tex_num], tex_x, tex_y));
	}
}
