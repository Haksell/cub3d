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

# include <stdio.h> // TODO remove

# define BUFFER_SIZE_3D 16384

# define USAGE_MANDATORY "Usage: ./cub3d *.cub"
# define OPEN_ERROR "File cannot be opened"
# define MALLOC_ERROR "Impossible to allocate heap memory"
# define READ_ERROR "Error while reading the file"

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

# define ID_NORTH "NO"
# define ID_SOUTH "SO"
# define ID_WEST "WE"
# define ID_EAST "EA"
# define ID_FLOOR "F"
# define ID_CEIL "C"

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 360
# define SPACES " \f\n\r\t\v"
# define MAP_CHARACTERS ".01"
# define PLAYER_CHARACTERS "NESW"
# define NON_WALL_CHARACTERS "0NESW"

# define SURFACES_CYLINDER 3
# define SURFACES_PLANE 1
# define SURFACES_SPHERE 1

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

typedef struct s_textures {
	void	*north;
	void	*east;
	void	*south;
	void	*west;
}	t_textures;

typedef struct s_data {
	t_vec2		**pixels; // either int ** or rm
	int			frame;
	t_mlx		mlx;
	t_map		map;
	t_infos		infos;
	t_textures	textures;
}	t_data;

/******************************************************************************/
/*                                                                            */
/*                                   DEBUG                                    */
/*                                                                            */
/******************************************************************************/

void		display_map(t_map *map); // TODO remove

/******************************************************************************/
/*                                                                            */
/*                                  DISPLAY                                   */
/*                                                                            */
/******************************************************************************/

int			render_frame(t_data *data);

/******************************************************************************/
/*                                                                            */
/*                                 MLX_TOOLS                                  */
/*                                                                            */
/******************************************************************************/

int			handle_key_down(int keycode, t_data *data);
bool		init_minilibx(t_data *data, char *window_title);

/******************************************************************************/
/*                                                                            */
/*                                  PARSING                                   */
/*                                                                            */
/******************************************************************************/

char		**get_lines(char *filename);
bool		parse_color(char *s, int *color);
bool		parse_file(t_data *data, int argc, char **argv);
bool		parse_infos(t_infos *infos, char ***lines);
bool		parse_map(t_map *map, char **lines);

/******************************************************************************/
/*                                                                            */
/*                                   UTILS                                    */
/*                                                                            */
/******************************************************************************/

int			arrlen(char **lines);
int			close_window(t_data *data);
bool		complain_bool(char *error_message);
int			complain_int(char *error_message);
void		*complain_ptr(char *error_message);
void		free_data(t_data *data);
bool		includes(char **arr, char *s);
void		init_data(t_data *data);
bool		is_close(double x, double y);

/******************************************************************************/
/*                                                                            */
/*                                    vec2                                    */
/*                                                                            */
/******************************************************************************/

t_vec2		vec2_add(t_vec2 v1, t_vec2 v2);
double		vec2_dist(t_vec2 v1, t_vec2 v2);
double		vec2_dist_squared(t_vec2 v1, t_vec2 v2);
t_vec2		vec2_div(t_vec2 v, double t);
double		vec2_dot(t_vec2 v1, t_vec2 v2);
double		vec2_length(t_vec2 v);
double		vec2_length_squared(t_vec2 v);
t_vec2		vec2_mul(t_vec2 v1, t_vec2 v2);
t_vec2		vec2_negate(t_vec2 v);
t_vec2		vec2_scale(t_vec2 v, double t);
t_vec2		vec2_sub(t_vec2 v1, t_vec2 v2);
t_vec2		vec2_unit(t_vec2 v);

#endif
