/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:28:18 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/05 17:08:54 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*skip_lines(int fd, int lines_to_skip)
{
	char	*line;
	int		i;

	i = 0;
	while (i < lines_to_skip)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		free(line);
		i++;
	}
	return (get_next_line(fd));
}

static char	**allocate_map(int size)
{
	char	**map;

	map = malloc(sizeof(char *) * size);
	if (!map)
	{
		error_handler("Error allocating memory for map");
		return (NULL);
	}
	return (map);
}

static int	read_map_lines(int fd, char **map)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (i);
}

char	**get_map(t_base *base)
{
	int		fd;
	char	**map;
	int		map_size;

	fd = open(base->map_name, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	map = allocate_map(200);
	if (!map)
		return (close(fd), NULL);
	if (!skip_lines(fd, 7))
		return (free(map), close(fd), NULL);
	map_size = read_map_lines(fd, map);
	if (map_size == 0)
	{
		free(map);
		close(fd);
		return (error_handler("Error reading map lines"), NULL);
	}
	close(fd);
	return (map);
}
