#include "../../includes/cub3d.h"

void toggle_door(t_base *base)
{
    // Calculer la position devant le joueur
    int check_x = (int)(base->player->pos_x + base->player->dir_x);
    int check_y = (int)(base->player->pos_y + base->player->dir_y);
    
        // Vérifier si une porte est présente
      if (base->data->map[check_x][check_y] == 'D')
         base->data->map[check_x][check_y] = 'O';  // Ouvrir la porte
      else if (base->data->map[check_x][check_y] == 'O')
           base->data->map[check_x][check_y] = 'D';  // Fermer la porte
}

int is_door(char c)
{
    return (c == 'D' || c == 'O');
} 