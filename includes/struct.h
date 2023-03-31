#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_scene {
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*world;
	int			nb_obj;
}	t_scene;

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
	t_scene	scene;
}	t_data;

#endif