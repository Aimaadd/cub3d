/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:33 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/02 13:45:34 by rpepi            ###   ########.fr       */
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

#define TILE_SIZE 30
#define FOV 60

//BUFFER
#define BUFFER_SIZE 1024

typedef struct s_ray
{
	double ray_ngl;
	double distance;
	int  flag;
} t_ray;

typedef struct s_mlx 
{
	void	*win;
	void	*ptr;
	void	*img;
	int		width;
	t_ray	*ray;
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
	char	**map;
	int		character;
	int		closed;
	int		invalid;
	
}	t_map;

typedef struct s_player
{
	double  pos_x;
	double  pos_y;
	double  dir_x;     // Direction vecteur X
	double  dir_y;     // Direction vecteur Y
	double  plane_x;   // Plan caméra X
	double  plane_y;   // Plan caméra Y
	double  move_speed;
	double  rot_speed;
	char    dir;       // Direction initiale (N,S,E,W)
}   t_player;

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

void	error_handler(char *message);

// +++++++++++++++ map_reader.c +++++++++++++++

char	**get_map(t_base *base);

// +++++++++++++++ struct_handler.c +++++++++++++++

t_textures *fill_textures(t_textures *text, char *param);


// +++++++++++++++ parse_map.c ++++++++++++++++++

int valid_map(t_base *base);

// +++++++++++++++ raycast.c ++++++++++++++++++++

void    init_player_direction(t_player *player);
void    raycasting(t_base *base);
void draw_vertical_line(t_data *data, int x, int start, int end, int color);

// +++++++++++++++ moves.c ++++++++++++++++++++

void    move_forward(t_base *base);
void    move_backward(t_base *base);
void    move_left(t_base *base);
void    move_right(t_base *base);

// +++++++++++++++ rotation.c ++++++++++++++++++++

void    rotate_right(t_base *base);
void    rotate_left(t_base *base);

// +++++++++++++++ events.c ++++++++++++++++++++

int     handle_keypress(int keycode, t_base *base);
int     handle_close(t_base *base);
void    game_loop(t_base *base);

#endif