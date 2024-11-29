/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:07:15 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/28 18:24:15 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int char_reader(char c, int i, int j, t_base *base)
{
    if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E'
        || c == '\n' || c == ' ')
    {
        if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
        {
            base->map->character++;
            base->player->dir = c;
            base->player->pos_y = j;
            base->player->pos_x = i;
        }
        return (0);
    }
    else
        return (error_handler("Error"), 1);   
    return (1);
}

static int read_map(t_base *base)
{
    int i;
    int j;
    i = 0;
    while (base->data->map[i])
    {
        j = 0;
        while (base->data->map[i][j])
        {
            if (char_reader(base->data->map[i][j], i, j, base) == 1)
                return (1);
            j++;
        }
        i++;
    }
    if (base->map->character > 1)
        return (1);
    if (base->map->character == 0)
        return (1);
    return (printf("map is valid\n"), 0);
}

int valid_map(t_base *base)
{
    if (read_map(base) == 1)
        return (1);
    // if (map_infos(base) == 1)
    //     return (1);
    return (0);
}