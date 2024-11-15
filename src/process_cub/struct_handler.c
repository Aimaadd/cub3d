/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:50:17 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/15 16:14:02 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_textures	*fill_textures(t_textures *text, char *param)
{
	if (!param && text->set != 1)
		return (NULL);
	else if (ft_strncmp(param, "NO ", 3) == 0 && text->NO != param)
		text->NO = ft_strdup(param);
	else if (ft_strncmp(param, "F ", 2) == 0 && text->F != param)
		text->F = ft_strdup(param);
	else if (ft_strncmp(param, "EA ", 3) == 0 && text->EA != param)
		text->EA = ft_strdup(param);
	else if (ft_strncmp(param, "C ", 2) == 0 && text->C != param)
		text->C = ft_strdup(param);
	else if (ft_strncmp(param, "SO ", 3) == 0 && text->SO != param)
		text->SO = ft_strdup(param);
	else if (ft_strncmp(param, "WE ", 3) == 0 && text->WE != param)
		text->WE = ft_strdup(param);
	else
	{
		error_handler("Error in textures assignement");
		return (NULL);
	}
	if (text->NO && text->F && text->EA && text->C && text->SO && text->WE)
		text->set = 1;
	return (text);
}
