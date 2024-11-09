/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:39:54 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/09 19:42:00 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	char_scanner(char c)
{
	unsigned int	i;
	char			set[6] = {'0', '1', 'N', 'S', 'E', 'W'};
	i = 0;
	while (i < sizeof(set) / sizeof(set[0]))
	{
		if (c == set[i++])
			return (1);
	}
	return (0);
}

static int	read_valid(int fd)
{
	char	*buffer;
	int		b_read;
	int		i;

	i = 0;
	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		error_handler("Allocation failed");
	while ((b_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		buffer[b_read] = '\0';
		while (buffer[i++])
		{
			char_scanner(buffer[i]);
		}
	}
	if (b_read < 0)
		error_handler("Can't open operation file");
	return (0);
}
int	read_map_file(char *map_name)
{
	int	fd;
	// char **map;
	
	// map = NULL;
	// printf("%s\n", map[0]);
	fd = open(map_name, O_RDONLY);
	if (fd < 0 || !map_name)
	{
		perror("Can't open file");
		exit(EXIT_FAILURE);	
	}
	else
		read_valid(fd);
	return (0);
}