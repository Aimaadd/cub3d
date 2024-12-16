/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:18:28 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/16 11:39:34 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_text(t_textures *text)
{
	if (text->NO)
		free(text->NO);
	if (text->SO)
		free(text->SO);
	if (text->WE)
		free(text->WE);
	if (text->EA)
		free(text->EA);
	if (text->F)
		free(text->F);
	if (text->C)
		free(text->C);
}

void	free_all(t_base *base)
{
	if (base->map)
	{
		if (base->map->fparams)
			free(base->map->fparams);
		free(base->map);
	}
	if (base->player)
		free(base->player);
	if (base->data)
		free(base->data);
	if (base->mlx)
		free(base->mlx);
	if (base->text)
	{
		free_text(base->text);
		free(base->text);
	}
	write(1, "Error\n", 6);
	free(base);
	exit(1);
}
