/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.b\e>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:39:54 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/14 17:39:22 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// static int	is_valid_param(char *param)
// {
// 	if (ft_strncmp(param, "NO ", 3) == 0 || ft_strncmp(param, "F ", 2) == 0
// 		|| ft_strncmp(param, "EA ", 3) == 0 || ft_strncmp(param, "C ", 2) == 0
// 		|| ft_strncmp(param, "SO ", 3) == 0 || ft_strncmp(param, "WE ", 3) == 0
// 		|| ft_strncmp(param, "\n", 1) == 0)
// 		return (0);
// 	return (1);
// }

// static int	settings_scan(char *buffer)
// {
// 	if (is_valid_param(buffer) != 0)
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

static int	process_buffer(t_base *base, char *buffer)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(buffer, '\n');
	while (split[i])
	{
		// if (settings_scan(split[i]) != 0)
		// {
		// 	free_all(base);
		// 	return (1);
		// }
		fill_textures(base->text, split[i]);
		if (base->text->set == 1)
			break ;
		i++;
	}
	if (text_checker(base->text) == 1)
	{
		ft_free_split(split);
		return (printf("wrong text\n"), exit(1), 1);
	}
	ft_free_split(split);
	return (0);
}

static int	read_valid(int fd, t_base *base)
{
	char	*buffer;
	int		b_read;

	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (free_all(base), 1);
	b_read = read(fd, buffer, BUFFER_SIZE - 1);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		if (process_buffer(base, buffer) != 0)
			return (free_all(base), 1);
		if (buffer[0] == '\0')
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE - 1);
	}
	if (b_read < 0)
		return (free_all(base), 1);
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
		base->data->map = get_map(base);
		if (base->data->map)
		{
			if (valid_map(base) == 1)
				return (NULL);
		}
	}
	close(fd);
	return (base);
}
