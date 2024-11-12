/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:39:54 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/12 20:42:14 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_param(char *param)
{
    printf("param : %s\n", param);
    if (ft_strncmp(param, "NO ", 3) == 0 || ft_strncmp(param, "F ", 2) == 0
        || ft_strncmp(param, "EA ", 3) == 0 || ft_strncmp(param, "C ", 2) == 0
        || ft_strncmp(param, "SO ", 3) == 0 || ft_strncmp(param, "WE ", 3) == 0
        || ft_strncmp(param, "\n", 1) == 0)
        	return (0);
	else
	{
		printf("problem\n");
		return (1);
	}
    return (1);
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

static int settings_scan(char *buffer)
{
    if (is_valid_param(buffer) != 0)
    {
        return (error_handler("Invalid parameter"), 1);
    }
    return (0);
}

static int	handle_error(char *buffer, int fd, char *msg)
{
	free(buffer);
	close(fd);
	error_handler(msg);
	return (1);
}

static int process_buffer(char *buffer)
{
    char    **split;
    int     i;

    i = 0;
    split = ft_split(buffer, '\n');
    while (split[i])
    {
        if (settings_scan(split[i]) != 0)
        {
            ft_free_split(split);
            return (1);
        }
        i++;
    }
    ft_free_split(split);
    return (0);
}

static int read_valid(int fd)
{
	char *buffer;
	int b_read;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (handle_error(buffer, fd, "Allocation failed"));
	b_read = read(fd, buffer, BUFFER_SIZE - 1);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		if (process_buffer(buffer) != 0)
			return (handle_error(buffer, fd, "Settings scan failed"));
		if (buffer[0] == '\0')
			break;
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
		return (NULL);	
	}
	else
	{
		read_valid(fd);
		map = get_map(map_name);
	}
	return (map);
}