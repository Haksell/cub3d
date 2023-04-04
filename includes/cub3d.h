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

# define ID_NORTH "NO"
# define ID_SOUTH "SO"
# define ID_WEST "WE"
# define ID_EAST "EA"
# define ID_FLOOR "F"
# define ID_CEIL "C"

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 360
# define MAX_DEPTH 25
# define SHADOW_ACNE_FIX 1e-3
# define SPACES " \f\n\r\t\v"

# define SURFACES_CYLINDER 3
# define SURFACES_PLANE 1
# define SURFACES_SPHERE 1

/******************************************************************************/
/*                                                                            */
/*                                  STRUCTS                                   */
/*                                                                            */
/******************************************************************************/

typedef struct s_vec3 {
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_map {
	int		**grid;
	int		width;
	int		height;
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
	t_vec3		**pixels; // either int ** or rm
	int			frame;
	t_mlx		mlx;
	t_map		map;
	t_infos		infos;
	t_textures	textures;
}	t_data;

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
bool		init_pixels(t_data *data);
bool		is_close(double x, double y);

// vec3
t_vec3		vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2);
double		vec3_dist(t_vec3 v1, t_vec3 v2);
double		vec3_dist_squared(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_div(t_vec3 v, double t);
double		vec3_dot(t_vec3 v1, t_vec3 v2);
double		vec3_length(t_vec3 v);
double		vec3_length_squared(t_vec3 v);
t_vec3		vec3_mul(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_negate(t_vec3 v);
t_vec3		vec3_scale(t_vec3 v, double t);
t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_unit(t_vec3 v);

#endif
