#include "../../includes/cub3d.h"

void    move_forward(t_base *base)
{
    double new_x = base->player->pos_x + base->player->dir_x * base->player->move_speed;
    double new_y = base->player->pos_y + base->player->dir_y * base->player->move_speed;
    
    char next_pos = base->data->map[(int)new_x][(int)base->player->pos_y];
    if (next_pos != '1' && (next_pos != 'D'))  // On peut traverser les portes ouvertes ('O')
        base->player->pos_x = new_x;
    
    next_pos = base->data->map[(int)base->player->pos_x][(int)new_y];
    if (next_pos != '1' && (next_pos != 'D'))
        base->player->pos_y = new_y;
}

void    move_backward(t_base *base)
{
    double new_x = base->player->pos_x - base->player->dir_x * base->player->move_speed;
    double new_y = base->player->pos_y - base->player->dir_y * base->player->move_speed;
    
    char next_pos = base->data->map[(int)new_x][(int)base->player->pos_y];
    if (next_pos != '1' && (next_pos != 'D'))  // On peut traverser les portes ouvertes ('O')
        base->player->pos_x = new_x;
    
    next_pos = base->data->map[(int)base->player->pos_x][(int)new_y];
    if (next_pos != '1' && (next_pos != 'D'))
        base->player->pos_y = new_y;
}

void    move_left(t_base *base)
{
    double new_x = base->player->pos_x - base->player->plane_x * base->player->move_speed;
    double new_y = base->player->pos_y - base->player->plane_y * base->player->move_speed;
    
    char next_pos = base->data->map[(int)new_x][(int)base->player->pos_y];
    if (next_pos != '1' && (next_pos != 'D'))  // On peut traverser les portes ouvertes ('O')
        base->player->pos_x = new_x;
    
    next_pos = base->data->map[(int)base->player->pos_x][(int)new_y];
    if (next_pos != '1' && (next_pos != 'D'))
        base->player->pos_y = new_y;
}

void    move_right(t_base *base)
{
    double new_x = base->player->pos_x + base->player->plane_x * base->player->move_speed;
    double new_y = base->player->pos_y + base->player->plane_y * base->player->move_speed;
    
    char next_pos = base->data->map[(int)new_x][(int)base->player->pos_y];
    if (next_pos != '1' && (next_pos != 'D'))  // On peut traverser les portes ouvertes ('O')
        base->player->pos_x = new_x;
    
    next_pos = base->data->map[(int)base->player->pos_x][(int)new_y];
    if (next_pos != '1' && (next_pos != 'D'))
        base->player->pos_y = new_y;
} 