#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>

# define USAGE_MANDATORY "Usage: ./cub3d *.cub"
# define SPACY_LINE "Line contains only spaces and tabulations"
# define OPEN_ERROR "File cannot be opened"
# define MALLOC_ERROR "Impossible to allocate heap memory"
# define READ_ERROR "Error while reading the file"
# define INVALID_IDENTIFIER "Invalid identifier"

# define DOUBLE_AMBIENT "Too many ambient lights"
# define DOUBLE_CAMERA "Too many cameras"
# define DOUBLE_LIGHT "Too many lights"
# define ERROR_AMBIENT "Error parsing ambient light"
# define ERROR_CAMERA "Error parsing camera"
# define ERROR_LIGHT "Error parsing light"
# define NO_CAMERA "There is no camera"
# define NO_LIGHT "There is no light"
# define FOV_ERROR "Field of view is invalid"

# define ERROR_CYLINDER "Error parsing cylinder"
# define ERROR_PLANE "Error parsing plane"
# define ERROR_SPHERE "Error parsing sphere"

# define ERROR_MLX "Failed to initialize mlx"
# define ERROR_WINDOW "Failed to initialize window"
# define ERROR_IMAGE "Failed to initialize image"
# define ERROR_ADDR "Failed to initialize addr"

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 360
# define MAX_DEPTH 25
# define BUFFER_SIZE_RT 16384
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
}	t_map;

typedef struct s_mlx {
	int		bytes_per_pixel;
	int		line_length;
	int		*addr;
	void	*win;
	void	*img;
	void	*mlx;
}	t_mlx;

typedef struct s_data {
	int		frame;
	t_mlx	mlx;
	t_vec3	**pixels;
	t_map	map;
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
bool		init_minilibx(t_mlx *mlx, char *window_title);

/******************************************************************************/
/*                                                                            */
/*                                  PARSING                                   */
/*                                                                            */
/******************************************************************************/

char		***get_words(char *filename);
bool		parse_map(t_map *map, int argc, char **argv);

/******************************************************************************/
/*                                                                            */
/*                                   UTILS                                    */
/*                                                                            */
/******************************************************************************/

int			arrlen(char **lines);
int			clamp(int x, int min, int max);
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
bool		vec3_near_zero(t_vec3 v);
t_vec3		vec3_negate(t_vec3 v);
t_vec3		vec3_scale(t_vec3 v, double t);
t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_unit(t_vec3 v);

#endif
