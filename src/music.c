/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:18:49 by pepi              #+#    #+#             */
/*   Updated: 2024/12/16 14:19:33 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	play_music(void)
{
	char *music_args[] = {"afplay", "./music/music.mp3", NULL};
    execvp("afplay", music_args);
    perror("Erreur lors du lancement de la musique");
    exit(1);
}