/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:39:54 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/11 16:04:25 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_param(char *param)
{
	return (ft_strncmp(param, "NO", 2) == 0 || ft_strncmp(param, "F", 1) == 0
		|| ft_strncmp(param, "EA", 2) == 0 || ft_strncmp(param, "C", 1) == 0
		|| ft_strncmp(param, "SO", 2) == 0 || ft_strncmp(param, "WE", 2) == 0);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	settings_scan(char *buffer)
{
	char	**params;
	int		i;

	params = ft_split(buffer, '\n');
	if (!params)
		return (error_handler("Allocation failed"), 1);
	i = 0;
	while (i < 6)
	{
		if (!params[i] || !is_valid_param(params[i]))
		{
			ft_free_split(params);
			return (error_handler("Invalid parameter in .cub file"), 1);
		}
		i++;
	}
	ft_free_split(params);
	return (0);
}

static int	handle_error(char *buffer, int fd, char *msg)
{
	free(buffer);
	close(fd);
	error_handler(msg);
	return (1);
}

static int	process_buffer(char *buffer, int *i)
{
	if (*i < 6)
	{
		if (settings_scan(buffer) != 0)
			return (1);
		(*i)++;
	}
	return (0);
}

static int	read_valid(int fd)
{
	char	*buffer;
	int		b_read;
	int		i;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (handle_error(buffer, fd, "Allocation failed"));
	i = 0;
	b_read = read(fd, buffer, BUFFER_SIZE - 1);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		if (process_buffer(buffer, &i) != 0)
			return (handle_error(buffer, fd, "Settings scan failed"));
		b_read = read(fd, buffer, BUFFER_SIZE - 1);
	}
	if (b_read < 0)
		return (handle_error(buffer, fd, "Can't open operation file"));
	free(buffer);
	close(fd);
	return (0);
}

char	**read_map_file(char *map_name)
{
	int	fd;
	char **map;
	
	map = NULL;
	fd = open(map_name, O_RDONLY);
	if (fd < 0 || !map_name)
	{
		perror("Can't open file");
		exit(EXIT_FAILURE);	
	}
	else
	{
		read_valid(fd);
		map = get_map(map_name);
	}
	return (map);
}