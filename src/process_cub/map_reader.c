/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:28:18 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/12 16:32:44 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char *skip_lines(char *line, int fd)
{
    int i;

    i = 0;
    while (i < 7)
    {
        line = get_next_line(fd);
        i++;
    }
    return (line);
}

char **get_map(char *map_name)
{
    int fd;
    char *line;
    int i;
    char **map;

    line = NULL;
    i = 0;
    fd = open(map_name, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return NULL;
    }
    map = malloc(sizeof(char *) * 200);
    if (!map)
        return (error_handler("Allocation failed"), close(fd), NULL);
    line = skip_lines(line, fd);
    while (line)
    {
        map[i] = malloc(strlen(line) + 1);
        if (!map[i])
            return (error_handler("Allocation failed"), close(fd), NULL);
        strcpy(map[i], line);
        free(line);
        i++;
        line = get_next_line(fd);
    }
    map[i] = NULL;
    close(fd);
    return map;
}