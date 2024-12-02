#include "../../includes/cub3d.h"

void    rotate_right(t_base *base)
{
    double old_dir_x = base->player->dir_x;
    base->player->dir_x = base->player->dir_x * cos(-base->player->rot_speed) - 
                         base->player->dir_y * sin(-base->player->rot_speed);
    base->player->dir_y = old_dir_x * sin(-base->player->rot_speed) + 
                         base->player->dir_y * cos(-base->player->rot_speed);
    
    double old_plane_x = base->player->plane_x;
    base->player->plane_x = base->player->plane_x * cos(-base->player->rot_speed) - 
                           base->player->plane_y * sin(-base->player->rot_speed);
    base->player->plane_y = old_plane_x * sin(-base->player->rot_speed) + 
                           base->player->plane_y * cos(-base->player->rot_speed);
}

void    rotate_left(t_base *base)
{
    double old_dir_x = base->player->dir_x;
    base->player->dir_x = base->player->dir_x * cos(base->player->rot_speed) - 
                         base->player->dir_y * sin(base->player->rot_speed);
    base->player->dir_y = old_dir_x * sin(base->player->rot_speed) + 
                         base->player->dir_y * cos(base->player->rot_speed);
    
    double old_plane_x = base->player->plane_x;
    base->player->plane_x = base->player->plane_x * cos(base->player->rot_speed) - 
                           base->player->plane_y * sin(base->player->rot_speed);
    base->player->plane_y = old_plane_x * sin(base->player->rot_speed) + 
                           base->player->plane_y * cos(base->player->rot_speed);
} 