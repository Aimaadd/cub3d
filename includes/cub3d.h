/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:33 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/09 19:40:42 by abentaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"

//RESOLUTION 
#define WIDTH 1920
#define HEIGHT 1080

//BUFFER
#define BUFFER_SIZE 1024

typedef struct s_mlx 
{
	void	*win;
	void	*ptr;
	int		width;
	int		length;
}	t_mlx;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_base
{
	t_mlx *mlx;
}	t_base;

//  ++++++++++++++++ window.c ++++++++++++++++
t_base  *initialization(t_base *base);

// +++++++++++++++ map_reader.c ++++++++++++++

int read_map_file(char *map);

// ++++++++++++++++ error.c ++++++++++++++++

void    error_handler(char *message);

#endif