/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:33 by abentaye          #+#    #+#             */
/*   Updated: 2024/11/15 16:57:08 by abentaye         ###   ########.fr       */
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
#define WIDTH 1280
#define HEIGHT 720

//WALL TEXTURES
#define NORTH
#define SOUTH
#define WEST
#define EAST

//BUFFER
#define BUFFER_SIZE 1024


typedef struct s_mlx 
{
	void	*win;
	void	*ptr;
	int		width;
	int		length;
}	t_mlx;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir;
}	t_player;

typedef struct s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	int		set;
}	t_textures;

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
	char		*map_name;
	t_player	*player;
	t_data		*data;
	t_mlx		*mlx;
	t_textures	*text;
}	t_base;

//  ++++++++++++++++ window.c ++++++++++++++++

void	initialization(t_base *base, char **argv);

// +++++++++++++++ file_reader.c ++++++++++++++

t_base	*read_map_file(t_base *base);
void	ft_free_split(char **split);

// ++++++++++++++++ error.c +++++++++++++++++++

void	error_handler(char *message);

// +++++++++++++++ map_reader.c +++++++++++++++

char	**get_map(char *map_name);

// +++++++++++++++ struct_handler.c +++++++++++++++

t_textures *fill_textures(t_textures *text, char *param);


// +++++++++++++++ parse_map.c ++++++++++++++++++

int valid_map(t_base *base);

#endif