#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include "error.h"
# include "struct.h"

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

# ifndef M_PI
#  define M_PI 3.141592653589793
# endif
# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 360
# define MAX_DEPTH 25
# define BUFFER_SIZE_RT 16384
# define SHADOW_ACNE_FIX 1e-3
# define SPACES " \f\n\r\t\v"

# define SURFACES_CYLINDER 3
# define SURFACES_PLANE 1
# define SURFACES_SPHERE 1

typedef bool	(*t_scatter_func)(t_ray, t_hit, t_vec3 *, t_ray *);

/******************************************************************************/
/*                                                                            */
/*                                  DISPLAY                                   */
/*                                                                            */
/******************************************************************************/

t_ray		get_ray(const t_camera *camera, double s, double t);
t_vec3		ray_at(t_ray ray, double t);
t_vec3		ray_color(t_ray ray, t_scene *scene, int depth);
t_vec3		reflect(t_vec3 v, t_vec3 n);
double		reflectance(double cosine, double ref_idx);
t_vec3		refract(t_vec3 v, t_vec3 n, double ir);
t_vec3		get_light_impact(t_scene *scene, t_hit *hit, t_ray ray);
int			render_frame(t_data *data);
bool		scatter(t_ray ray, t_hit hit,
				t_vec3 *attenuation, t_ray *scattered);
void		set_face_normal(t_hit *hit, t_ray *ray, t_vec3 *outward_normal);

/******************************************************************************/
/*                                                                            */
/*                                    HIT                                     */
/*                                                                            */
/******************************************************************************/

bool		hit_disk(t_hit *hit, const t_disk *disk, t_ray *ray,
				t_interval interval);
bool		hit_sphere(t_hit *hit, const t_sphere *sphere, t_ray *ray,
				t_interval interval);
bool		hit_plane(t_hit *hit, const t_plane *plane, t_ray *ray,
				t_interval interval);
bool		hit_tube(t_hit *hit, const t_tube *tube, t_ray *ray,
				t_interval interval);
bool		hit_world(t_hit *hit, t_scene *scene, t_ray *ray,
				t_interval *interval);

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

bool		ft_atod(char *s, double *ans);
bool		ft_atod_range(char *s, double *ans, double min, double max);
char		***get_words(char *filename);
bool		parse_ambient(t_scene *scene, char **line);
bool		parse_camera(t_scene *scene, char **line);
bool		parse_color(char *s, t_vec3 *color);
bool		parse_coord(char *s, t_vec3 *coord);
bool		parse_cylinder(t_scene *scene, char **line, int *current_object);
bool		parse_light(t_scene *scene, char **line);
bool		parse_normalized_vector(char *s, t_vec3 *vector);
bool		parse_plane(t_scene *scene, char **line, int *current_object);
bool		parse_scene(t_scene *scene, int argc, char **argv);
bool		parse_sphere(t_scene *scene, char **line, int *current_object);

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
double		get_random_double(void);
double		get_random_double_range(double min, double max);
t_vec3		get_random_in_hemisphere(t_vec3 normal);
t_vec3		get_random_in_unit_disk(void);
t_vec3		get_random_in_unit_sphere(void);
t_vec3		get_random_unit_vector(void);
bool		includes(char **arr, char *s);
bool		in_interval(t_interval interval, double x);
bool		init_pixels(t_data *data);
bool		is_close(double x, double y);
void		print_vec3(char *name, t_vec3 v); // TODO remove

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
