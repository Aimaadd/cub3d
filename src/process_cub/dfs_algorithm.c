/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:50:23 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/09 21:58:51 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool dfs(char **map, int x, int y, char new_color, char old_color, int rows, int cols)
{
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        return false; // Reached the boundary of the map
    // if (map[x][y] != old_color)
        // return true;
    if (!map[x][y])
        return false;
    if (map[x][y] == '1' || map[x][y] == 'o')
        return true;
    map[x][y] = new_color;

    bool up = dfs(map, x - 1, y, new_color, old_color, rows, cols);
    bool down = dfs(map, x + 1, y, new_color, old_color, rows, cols);
    bool left = dfs(map, x, y - 1, new_color, old_color, rows, cols);
    bool right = dfs(map, x, y + 1, new_color, old_color, rows, cols);

    return up && down && left && right;
}

int floodfill(t_base *base)
{
    char nc = 'o';
    int x = base->player->pos_x;
    int y = base->player->pos_y;
    char oc = base->data->map[x][y];
    int rows = 0;
    int cols = ft_strlen(base->data->map[0]);

    base->data->map[x][y] = '0';
    if (oc == '1' || oc == 'o')
        return (1);
    while (base->data->map[rows])
        rows++;
    if (dfs(base->data->map, x, y, nc, oc, rows, cols) == true)
        return (0);
    else
        return (1);
}
