/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:50:17 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/16 18:15:08 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	text_checker(t_textures *text)
{
	if ((open(text->NO, O_RDONLY)) == -1)
		return (printf("error texutre\n"), 1);
	if ((open(text->EA, O_RDONLY)) == -1)
		return (printf("error texutre\n"), 1);
	if ((open(text->SO, O_RDONLY)) == -1)
		return (printf("error texutre\n"), 1);
	if ((open(text->WE, O_RDONLY)) == -1)
		return (printf("error texutre\n"), 1);
	printf("Textures are valid\n");
	return (0);
}

static int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char	*param_format(char *param)
{
	int		i;
	int		j;
	char	*formed;

	formed = (char *)malloc(strlen(param) - 1);
	i = 2;
	j = 0;
	while (param[i])
	{
		if (param[i] == '\n')
			break ;
		if (ft_isspace(param[i]) == 0)
		{
			formed[j] = param[i];
			j++;
		}
		i++;
	}
	formed[j] = '\0';
	return (formed);
}

t_textures	*fill_textures(t_textures *text, char *param)
{
	if (!param && text->set != 1)
		return (NULL);
	else if (ft_strncmp(param, "NO ", 3) == 0 && text->NO != param)
		text->NO = param_format(param);
	else if (ft_strncmp(param, "EA ", 3) == 0 && text->EA != param)
		text->EA = param_format(param);
	else if (ft_strncmp(param, "SO ", 3) == 0 && text->SO != param)
		text->SO = param_format(param);
	else if (ft_strncmp(param, "WE ", 3) == 0 && text->WE != param)
		text->WE = param_format(param);
	else if (ft_strncmp(param, "F ", 2) == 0 && text->F != param)
		text->F = param_format(param);
	else if (ft_strncmp(param, "C ", 2) == 0 && text->C != param)
		text->C = param_format(param);
	else
	{
		free_text(text);
		return (NULL);
	}
	if (text->NO && text->EA && text->SO && text->WE && text->F && text->C)
	{
		text->set = 1;
		return (text);
	}
	return (text);
}
