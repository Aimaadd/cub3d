/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:07:15 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/02 14:21:53 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int char_reader(char c, int i, int j, t_base *base)
{
    if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E'
        || c == '\n' || c == ' ' || c == 'D' || c == 'O')
    {
        if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
        {
            base->map->character++;
            base->player->dir = c;
            base->player->pos_y = j;
            base->player->pos_x = i;
        }
        else if (c == 'D' || c == 'O')
        {
            if (i == 0 || !base->data->map[i+1] || j == 0 || 
                j >= (int)ft_strlen(base->data->map[i]) - 1)
                return (error_handler("Error: Invalid door placement 1"), 1);
            
            if (!((i > 0 && base->data->map[i-1][j] == '1' && base->data->map[i+1][j] == '1') ||
                (j > 0 && base->data->map[i][j-1] == '1' && base->data->map[i][j+1] == '1')))
                return (error_handler("Error: Door must be between two walls"), 1);
            
            return (0);
        }
        return (0);
    }
    else
        return (error_handler("Error: Invalid character in map"), 1);   
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

static int check_door_surroundings(t_base *base)
{
    int i;
    int j;

    i = 0;
    while (base->data->map[i])
    {
        j = 0;
        while (base->data->map[i][j])
        {
            if (base->data->map[i][j] == 'D' || base->data->map[i][j] == 'O')
            {
                if (i == 0 || !base->data->map[i+1] || j == 0 || 
                    !base->data->map[i][j+1])
                    return (error_handler("Error: Door cannot be on map edge"), 1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int valid_map(t_base *base)
{
    if (read_map(base) == 1)
        return (1);
    if (check_door_surroundings(base) == 1)
        return (1);
    return (0);
}