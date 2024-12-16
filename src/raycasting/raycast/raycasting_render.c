/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:01:13 by rpepi             #+#    #+#             */
/*   Updated: 2024/12/16 18:12:39 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

unsigned int create_rgb(char *color)
{
    char    **split;
    int     r;
    int     g;
    int     b;
    unsigned int rgb;

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
    
    r = (r > 255) ? 255 : r; //si supérieur à 255, on met 255
    g = (g > 255) ? 255 : g;
    b = (b > 255) ? 255 : b;
    r = (r < 0) ? 0 : r; //si inférieur à 0, on met 0
    g = (g < 0) ? 0 : g;
    b = (b < 0) ? 0 : b;
    
    rgb = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff); //on met les valeurs dans rgb
    
    ft_free_split(split);
    return (rgb);
}

void raycasting(t_base *base)
{
    t_ray_calc  rc;
    int         x;

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
    mlx_put_image_to_window(base->mlx->ptr, base->mlx->win, 
        base->data->img, 0, 0);
}

void render_wall(t_base *base, t_ray_calc *rc, int x)
{
	int tex_num;
	int tex_x;
	double wall_x;

	// Détermine quelle texture utiliser selon la direction du mur
	if (rc->side == 0)
	{
		tex_num = (rc->ray_dir_x > 0) ? 3 : 2;  // EA ou WE
		wall_x = base->player->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	}
	else
	{
		tex_num = (rc->ray_dir_y > 0) ? 1 : 0;  // SO ou NO
		wall_x = base->player->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	}
	wall_x -= floor(wall_x);

	// Calcule la coordonnée x de la texture
	tex_x = (int)(wall_x * base->textures[tex_num].width);
	if ((rc->side == 0 && rc->ray_dir_x < 0) || 
		(rc->side == 1 && rc->ray_dir_y > 0))
		tex_x = base->textures[tex_num].width - tex_x - 1;

	// Dessine la ligne texturée
	draw_textured_line(base->data, x, rc->draw_start, rc->draw_end,
					  &base->textures[tex_num], tex_x);
}

void draw_background(t_base *base)
{
    int x, y;
    unsigned int ceiling_color;
    unsigned int floor_color;
    
    ceiling_color = create_rgb(base->text->C);     // C 225,30,0
    floor_color = create_rgb(base->text->F);      // F 220,100,0
    
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            if (y < HEIGHT / 2)
                my_mlx_pixel_put(base->data, x, y, ceiling_color);
            else
                my_mlx_pixel_put(base->data, x, y, floor_color);
        }
    }
} 