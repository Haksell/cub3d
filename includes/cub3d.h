#ifndef MINIRT_H
# define MINIRT_H

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

# define USAGE_MANDATORY "Usage: ./minirt *.rt"
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
/*                                   BASIC                                    */
/*                                                                            */
/******************************************************************************/

typedef struct s_vec3 {
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ray {
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_interval {
	double	min;
	double	max;
}	t_interval;

/******************************************************************************/
/*                                                                            */
/*                                 MATERIALS                                  */
/*                                                                            */
/******************************************************************************/

typedef struct t_dielectric {
	double	ir;
}	t_dielectric;

typedef struct t_lambertian {
	t_vec3	albedo;
}	t_lambertian;

typedef struct t_metal {
	t_vec3	albedo;
	double	fuzz;
}	t_metal;

typedef enum e_material_type {
	MATERIAL_DIELECTRIC = 0,
	MATERIAL_LAMBERTIAN,
	MATERIAL_METAL,
}	t_material_type;

typedef union u_material_union {
	t_dielectric	dielectric;
	t_lambertian	lambertian;
	t_metal			metal;
}	t_material_union;

typedef struct t_material {
	t_material_type		type;
	t_material_union	u;
}	t_material;

/******************************************************************************/
/*                                                                            */
/*                                  OBJECTS                                   */
/*                                                                            */
/******************************************************************************/

typedef struct s_sphere {
	t_vec3		center;
	double		radius;
	t_vec3		color;
	t_material	material;
}	t_sphere;

typedef struct s_plane {
	t_vec3		coord;
	t_vec3		vector;
	t_vec3		color;
	t_material	material;
}	t_plane;

typedef struct s_disk {
	t_plane	plane;
	double	radius;
}	t_disk;

typedef struct s_tube {
	t_vec3		center;
	t_vec3		axis;
	double		radius;
	double		half_height;
	t_vec3		color;
	t_material	material;
}	t_tube;

typedef enum e_object_type {
	OBJECT_DISK = 0,
	OBJECT_PLANE,
	OBJECT_SPHERE,
	OBJECT_TUBE
}	t_object_type;

typedef union u_object_union {
	t_disk		disk;
	t_plane		plane;
	t_sphere	sphere;	
	t_tube		tube;
}	t_object_union;

typedef struct s_object {
	t_object_type	type;
	t_object_union	u;
}	t_object;

/******************************************************************************/
/*                                                                            */
/*                                  ELEMENTS                                  */
/*                                                                            */
/******************************************************************************/

typedef struct s_ambient {
	bool	exists;
	double	ratio;
	t_vec3	color;
}	t_ambient;

typedef struct s_camera {
	bool	exists;
	double	aspect_ratio;
	double	viewport_width;
	double	viewport_height;
	double	lens_radius;
	double	focus_dist;
	t_vec3	origin;
	t_vec3	orientation;
	t_vec3	lower_left;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	u;
	t_vec3	v;
}	t_camera;

typedef struct s_light {
	bool	exists;
	t_vec3	coord;
	double	brightness;
	t_vec3	color;
}	t_light;

/******************************************************************************/
/*                                                                            */
/*                                  GENERAL                                   */
/*                                                                            */
/******************************************************************************/

typedef struct s_hit {
	bool		front_face;
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_material	material;
}	t_hit;

typedef struct s_map {
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*world;
	int			nb_obj;
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

t_ray		get_ray(const t_camera *camera, double s, double t);
t_vec3		ray_at(t_ray ray, double t);
t_vec3		ray_color(t_ray ray, t_map *map, int depth);
t_vec3		reflect(t_vec3 v, t_vec3 n);
double		reflectance(double cosine, double ref_idx);
t_vec3		refract(t_vec3 v, t_vec3 n, double ir);
t_vec3		get_light_impact(t_map *map, t_hit *hit, t_ray ray);
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
bool		hit_world(t_hit *hit, t_map *map, t_ray *ray,
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
char		***get_words(char *filename);
bool		parse_ambient(t_map *map, char **line);
bool		parse_camera(t_map *map, char **line);
bool		parse_color(char *s, t_vec3 *color);
bool		parse_coord(char *s, t_vec3 *coord);
bool		parse_cylinder(t_map *map, char **line, int *current_object);
bool		parse_light(t_map *map, char **line);
bool		parse_normalized_vector(char *s, t_vec3 *vector);
bool		parse_plane(t_map *map, char **line, int *current_object);
bool		parse_map(t_map *map, int argc, char **argv);
bool		parse_sphere(t_map *map, char **line, int *current_object);

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
