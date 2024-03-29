/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:09:52 by axbrisse          #+#    #+#             */
/*   Updated: 2023/05/07 09:09:52 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

# define BUFFER_SIZE_3D 16384

# define USAGE "Usage: ./cub3d *.cub"
# define ERROR_OPEN "File cannot be opened"
# define ERROR_MALLOC "Impossible to allocate heap memory"
# define ERROR_READ "Error while reading the file"

# define ERROR_ADDR "Failed to initialize addr"
# define ERROR_IMAGE "Failed to initialize image"
# define ERROR_MLX "Failed to initialize mlx"
# define ERROR_TEXTURES "Failed to initialize textures"
# define ERROR_WINDOW "Failed to initialize window"

# define ERROR_PARSE_INFOS "Failed to parse infos"
# define ERROR_PARSE_MAP "Failed to parse map"
# define ERROR_INVALID_CHAR "Invalid character found in map"
# define ERROR_NO_PLAYER "No player found in map"
# define ERROR_MULTIPLAYER "Too many players found in map"
# define ERROR_DUPLICATE_COLOR "Duplicate colors"
# define ERROR_DUPLICATE_TEXTURE "Duplicate texture"
# define ERROR_PARSING_COLOR "Failed to parse color"
# define ERROR_INCOMPLETE_WALL "Wall is incomplete"
# define ERROR_PARSING_LINE "Failed to parse line"
# define ERROR_INVALID_IDENTIFIER "Invalid identifier"
# define ERROR_MAP_TOO_SMALL "Map is too small"
# define ERROR_EMPTY_LINE_IN_MAP "Empty line found in map"
# define ERROR_INCOMPLETE_INFORMATIONS "Some textures or colors are missing"

# define ID_NORTH "NO"
# define ID_SOUTH "SO"
# define ID_WEST "WE"
# define ID_EAST "EA"
# define ID_FLOOR "F"
# define ID_CEIL "C"

# define SPACES " \f\n\r\t\v"
# define MAP_CHARACTERS ".01"
# define PLAYER_CHARACTERS "NESW"
# define NON_WALL_CHARACTERS "0NESW"

# define CAMERA_FOV 0.66
# define SPEED 0.025
# define TURN 0.010471975511965976

/******************************************************************************/
/*                                                                            */
/*                                  STRUCTS                                   */
/*                                                                            */
/******************************************************************************/

typedef struct s_vec2 {
	double	x;
	double	y;
}	t_vec2;

typedef struct s_map {
	int		width;
	int		height;
	char	**grid;
}	t_map;

typedef struct s_infos {
	int		floor;
	int		ceil;
	char	*path_north_texture;
	char	*path_east_texture;
	char	*path_south_texture;
	char	*path_west_texture;
}	t_infos;

typedef struct s_mlx {
	int		bytes_per_pixel;
	int		line_length;
	int		*addr;
	void	*win;
	void	*img;
	void	*mlx;
}	t_mlx;

typedef struct s_texture {
	int				width;
	int				height;
	int				bytes_per_pixel;
	int				size_line;
	void			*img;
	unsigned int	*addr;
}	t_texture;

typedef struct s_textures {
	t_texture	north;
	t_texture	east;
	t_texture	south;
	t_texture	west;
}	t_textures;

typedef struct s_player {
	int		forward;
	int		right;
	int		clockwise;
	t_vec2	pos;
	t_vec2	dir;
}	t_player;

typedef struct s_interval {
	int	start;
	int	end;
}	t_interval;

typedef struct s_dda {
	int			map_x;
	int			map_y;
	int			tex_x;
	int			step_x;
	int			step_y;
	int			line_height;
	int			half_line_height;
	bool		is_vertical;
	double		camera_x;
	double		wall_x;
	t_vec2		ray_dir;
	t_vec2		side_dist;
	t_vec2		delta_dist;
	t_texture	texture;
}	t_dda;

typedef struct s_data {
	t_mlx		mlx;
	t_map		map;
	t_vec2		camera;
	t_infos		infos;
	t_player	player;
	t_textures	textures;
}	t_data;

/******************************************************************************/
/*                                                                            */
/*                                    MISC                                    */
/*                                                                            */
/******************************************************************************/

int			arrlen(char **lines);
int			clamp(int n, int min, int max);
int			close_window(t_data *data);
bool		complain_bool(char *error_message);
int			complain_int(char *error_message);
void		*complain_ptr(char *error_message);
void		free_data(t_data *data);
void		free_lines(char **lines);
void		init_data(t_data *data);
t_vec2		vec2_add(t_vec2 v1, t_vec2 v2);
t_vec2		vec2_rotate(t_vec2 v, double angle);
t_vec2		vec2_scale(t_vec2 v, double t);

/******************************************************************************/
/*                                                                            */
/*                                 MLX_TOOLS                                  */
/*                                                                            */
/******************************************************************************/

int			handle_key_press(int keycode, t_data *data);
int			handle_key_release(int keycode, t_data *data);
bool		init_minilibx(t_data *data, char *window_title);

/******************************************************************************/
/*                                                                            */
/*                                  PARSING                                   */
/*                                                                            */
/******************************************************************************/

char		**get_lines(char *filename);
bool		is_map_walled(t_map *map);
bool		parse_color(char *s, int *color);
bool		parse_file(t_data *data, int argc, char **argv);
bool		parse_infos(t_infos *infos, char ***lines);
bool		parse_map(t_data *data, char **lines);
bool		valid_characters(t_data *data);

/******************************************************************************/
/*                                                                            */
/*                                RENDER_FRAME                                */
/*                                                                            */
/******************************************************************************/

void		draw_column(t_data *data, t_dda *dda, int x);
int			render_frame(t_data *data);
void		update_player(t_data *data);

#endif
