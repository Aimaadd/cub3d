/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:39:54 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/23 11:19:51 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	size_map(char **split, int i)
{
	int	j;

	j = 0;
	while (split[j])
		j++;
	return (j - i + 1);
}

char	**new_get_map(t_base *base, char **split, int i)
{
	char	**map;
	int		j;
	int		line_len;
	int		split_len;
	int		max_height;

	j = 0;
	max_height = longest_line(split);
	map = malloc(sizeof(char *) * (max_height + 1));
	if (!map)
		return (free_all(base, "malloc failed"), NULL);

	line_len = size_map(split, i);
	while (j < max_height)
	{
		map[j] = malloc(sizeof(char) * (line_len + 1));
		if (!map[j])
			return (free_all(base, "malloc failed"), NULL);
		
		ft_memset(map[j], '1', line_len);
		map[j][line_len] = '\0';
		j++;
	}
	map[j] = NULL;

	j = 0;
	while (split[i])
	{
		split_len = ft_strlen(split[i]);
		for (int k = 0; k < split_len; k++)
		{
			if (split[i][k] != ' ' && split[i][k] != '\n')
				map[k][j] = split[i][k];
		}
		i++;
		j++;
	}

	if (base->player)
	{
		int temp = base->player->pos_x;
		base->player->pos_x = base->player->pos_y;
		base->player->pos_y = temp;
	}

	return (map);
}

static int	process_buffer(t_base *base, char *buffer)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(buffer, '\n');
	while (split[i])
	{
		fill_textures(base->text, split[i]);
		if (base->text->set == 1)
			break ;
		i++;
	}
	if (text_checker(base->text) == -1)
	{
		ft_free_split(split);
		return (free_all(base, "text are not available"), -1);
	}
	base->data->map = new_get_map(base, split, i + 1);
	ft_free_split(split);
	return (i);
}

static int	read_valid(int fd, t_base *base)
{
	char	*buffer;
	int		b_read;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (free_all(base, "malloc failed"), 1);
	b_read = read(fd, buffer, BUFFER_SIZE - 1);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		if (process_buffer(base, buffer) == -1)
			return (free_all(base, "malloc failed"), 1);
		if (buffer[0] == '\0')
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE - 1);
	}
	if (b_read < 0)
		return (free_all(base, "malloc failed"), 1);
	free(buffer);
	close(fd);
	return (0);
}

t_base	*read_map_file(t_base *base)
{
	int		fd;

	fd = open(base->map_name, O_RDONLY);
	if (fd < 0 || !base->map_name)
	{
		perror("Can't open file");
		return (NULL);
	}
	else
	{
		if (read_valid(fd, base))
			return (NULL);
		if (base->data->map)
		{
			if (valid_map(base) == 1)
				return (free_all(base, "map is not valid"), NULL);
		}
	}
	close(fd);
	return (base);
}
