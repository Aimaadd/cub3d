/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:03:33 by abentaye          #+#    #+#             */
/*   Updated: 2024/12/16 15:26:45 by pepi             ###   ########.fr       */
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
# include <sys/types.h>
# include <signal.h>
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
	int		height;
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
	double  pos_x;
	double  pos_y;
	double  dir_x;
	double  dir_y;
	double  plane_x;
	double  plane_y;
	double  move_speed;
	double  rot_speed;
	char    dir;
	int		angle;
	double	fov;
}   t_player;

typedef struct s_ray_calc
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray_calc;

typedef struct s_texture_data {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_texture_data;

typedef struct s_base
{
	char		*map_name;
	t_player	*player;
	t_map		*map;
	t_data		*data;
	t_mlx		*mlx;
	t_textures	*text;
    t_texture_data  textures[4];  // NO, SO, WE, EA
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

void	print_map(char **map);

// +++++++++++++++ music.c ++++++++++++++++++++
void	play_music(void);

// +++++++++++++++ raycast.c ++++++++++++++++++++

void	raycasting(t_base *base);
void    init_ray_dir(t_base *base, t_ray_calc *rc, int x);
void    calc_step_dist(t_ray_calc *rc, t_player *player);
void    perform_dda(t_ray_calc *rc, t_base *base);
void    calc_wall_height(t_ray_calc *rc);
void    render_wall(t_base *base, t_ray_calc *rc, int x);
void    draw_background(t_base *base);
// +++++++++++++++ moves.c ++++++++++++++++++++

void	move_forward(t_base *base);
void	move_backward(t_base *base);
void	move_left(t_base *base);
void	move_right(t_base *base);

// +++++++++++++++ rotation.c ++++++++++++++++++++

void	rotate_right(t_base *base);
void	rotate_left(t_base *base);
void	rotate_vectors(t_player *player, double angle);

// +++++++++++++++ events.c ++++++++++++++++++++

void	clean_exit(t_base *base);
int		handle_keypress(int keycode, t_base *base);
int		handle_close(t_base *base);
int		handle_mouse_move(int x, int y, t_base *base);
int		handle_resize(int width, int height, t_base *base);
void	game_loop(t_base *base);

// +++++++++++++++ doors.c ++++++++++++++++++++
void	toggle_door(t_base *base);
int		is_door(char c);

// +++++++++++++++ init.c ++++++++++++++++++++

void	init_player_direction(t_player *player);
void	draw_vertical_line(t_data *data, int x, int start, int end, int color);

// +++++++++++++++ texture.c ++++++++++++++++++++

int		load_textures(t_base *base);
void	draw_textured_line(t_data *data, int x, int start, int end, \
		t_texture_data *tex, int tex_x);
void	free_textures(t_base *base);
int		verify_texture_dimensions(t_base *base);

// +++++++++++++++ utils.c ++++++++++++++++++++

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		init_textures_and_mlx(t_base *base);

#endif
