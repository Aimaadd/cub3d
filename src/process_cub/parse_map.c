/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:07:15 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/15 16:59:00 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int  map_infos(t_base *base)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (base->data->map[i][j])
    {
        if (base->data->map[i][j] == 'N' || base->data->map[i][j] == 'S'
            || base->data->map[i][j] == 'W' || base->data->map[i][j] == 'E')
            {
                base->player->pos_x = i;
                base->player->pos_y = j;
                base->player->dir = base->data->map[i][j];
                return (0);
            }
        j++;
        if (base->data->map[i][j] == '\n')
        {
            i++;
            j = 0;
        }
    }
    return (error_handler("No player found"), 1);
}

static int  read_map(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        if (map[j][i] != 'N' && map[j][i] != 'S' && map[j][i] != 'W'
            && map[j][i] != 'E' && map[j][i] != '0' && map[j][i] != '1')
            {
                printf("%c i : %d, j : %d\n", map[j][i], i, j   );
                return (error_handler("Invalid map"), 1);
            }
        if (map[j][i] == '\n')
            j++;
        i++;
    }
    return (printf("map is valid\n"), 0);
}

int valid_map(t_base *base)
{
    if (read_map(base->data->map) == 1)
        return (1);
    if (map_infos(base) == 1)
        return (1);
    return (0);
}