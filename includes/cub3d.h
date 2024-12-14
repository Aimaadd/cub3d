/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abentaye <abentaye@student.s19.b\e>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:33 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/14 16:26:33 by abentaye         ###   ########.fr       */
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
# include <stdbool.h>
# include "../minilibx/mlx.h"
# include "../src/get_next_line/get_next_line.h"

#define FILE_OK 42
#define FILE_ERR 21

//RESOLUTION 
#define WIDTH 1280
#define HEIGHT 720

//WALL TEXTURES
#define NORTH
#define SOUTH
#define WEST
#define EAST

#define TILE_SIZE 30
#define FOV 60

//BUFFER
#define BUFFER_SIZE 1024

typedef struct s_params {
    char    new_color;
    char    old_color;
    int     cols;
	int		rows;
}	t_params;

typedef struct s_mlx 
{
	void	*win;
	void	*ptr;
	void	*img;
	int		width;
	int		length;
}	t_mlx;

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

typedef struct s_map
{
	char		**map;
	int			character;
	int			closed;
	int			invalid;
	t_params	*fparams;

}	t_map;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	float	angle;
	float	fov;
	char	dir;
}	t_player;

typedef struct s_base
{
	char		*map_name;
	t_player	*player;
	t_map		*map;
	t_data		*data;
	t_mlx		*mlx;
	t_textures	*text;
}	t_base;

int init_mlx(t_base *base);

//  ++++++++++++++++ window.c ++++++++++++++++

void	initialization(t_base *base, char **argv);

// +++++++++++++++ file_reader.c ++++++++++++++

t_base	*read_map_file(t_base *base);
void	ft_free_split(char **split);

// ++++++++++++++++ error.c +++++++++++++++++++

void	free_all(t_base *base);
void 	free_text(t_textures *text);

// +++++++++++++++ map_reader.c +++++++++++++++

char	**get_map(t_base *base);

// +++++++++++++++ struct_handler.c +++++++++++++++

t_textures *fill_textures(t_textures *text, char *param);
int  text_checker(t_textures *text);


// +++++++++++++++ parse_map.c ++++++++++++++++++

int valid_map(t_base *base);

// +++++++++++++++ raycast.c ++++++++++++++++++++

void    game_loop(t_base *base);

// +++++++++++++++ dfs_algorithm.c ++++++++++++++++++++

int floodfill(t_base *base);

// +++++++++++++++ helper.c ++++++++++++++++++++

void	ft_free_split(char **split);

#endif