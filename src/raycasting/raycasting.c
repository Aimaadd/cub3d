#include "../../includes/cub3d.h"

void    init_player_direction(t_player *player)
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
    else if (player->dir == 'E')
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
    player->move_speed = 0.05;
    player->rot_speed = 0.05;
}

void draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
    int y = 0;
    while (y < start)
    {
        char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = 0x87CEEB;
        y++;
    }

    y = start;
    while (y < end)
    {
        char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
        y++;
    }

    y = end;
    while (y < HEIGHT)
    {
        char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = 0x808080;
        y++;
    }
}

void raycasting(t_base *base)
{
    ft_memset(base->data->addr, 0, base->data->line_length * HEIGHT);

    int x = 0;
    while (x < WIDTH)
    {
        double camera_x = 2 * x / (double)WIDTH - 1;
        double ray_dir_x = base->player->dir_x + base->player->plane_x * camera_x;
        double ray_dir_y = base->player->dir_y + base->player->plane_y * camera_x;

        int map_x = (int)base->player->pos_x;
        int map_y = (int)base->player->pos_y;

        double side_dist_x;
        double side_dist_y;
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double perp_wall_dist;

        int step_x;
        int step_y;
        int hit = 0;
        int side;

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (base->player->pos_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - base->player->pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (base->player->pos_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - base->player->pos_y) * delta_dist_y;
        }

        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (base->data->map[map_x][map_y] == '1' || base->data->map[map_x][map_y] == 'D')
                hit = 1;
        }

        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
        else
            perp_wall_dist = (side_dist_y - delta_dist_y);

        if (perp_wall_dist <= 0)
            perp_wall_dist = 0.1;

        int line_height = (int)(HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT)
            draw_end = HEIGHT - 1;

        int color = 0xFF0000;
        if (base->data->map[map_x][map_y] == 'D')
            color = 0x808080;
        else if (base->data->map[map_x][map_y] == 'O')
            color = 0x404040;
        if (side == 1)
            color = color / 2;

        draw_vertical_line(base->data, x, draw_start, draw_end, color);
        x++;
    }
    mlx_put_image_to_window(base->mlx->ptr, base->mlx->win, base->data->img, 0, 0);
}