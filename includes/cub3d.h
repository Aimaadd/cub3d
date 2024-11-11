/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:33 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/11 17:32:25 by abentaye         ###   ########.fr       */
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
# include "../src/get_next_line/get_next_line.h"

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
	char	**map;
}	t_data;

typedef struct s_base
{
	t_data	*data;
	t_mlx	*mlx;
}	t_base;

//  ++++++++++++++++ window.c ++++++++++++++++
void	initialization(t_base *base);

// +++++++++++++++ file_reader.c ++++++++++++++

char	**read_map_file(char *map);
void	ft_free_split(char **split);

// ++++++++++++++++ error.c +++++++++++++++++++

void	error_handler(char *message);

// +++++++++++++++ map_reader.c +++++++++++++++

char	**get_map(char *map_name);

#endif