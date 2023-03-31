#include "minirt.h"

bool	parse_ambient(t_scene *scene, char **line)
{
	const int	length = arrlen(line);

	if (scene->ambient.exists)
		return (complain_bool(DOUBLE_AMBIENT));
	if (length != 3
		|| !ft_atod_range(line[1], &scene->ambient.ratio, 0, 1)
		|| !parse_color(line[2], &scene->ambient.color))
		return (complain_bool(ERROR_AMBIENT));
	scene->ambient.exists = true;
	scene->ambient.color = vec3_scale(scene->ambient.color,
			scene->ambient.ratio / 255);
	return (true);
}

static void	define_camera(t_camera *camera, double fov)
{
	camera->exists = true;
	camera->lens_radius = 0;
	camera->focus_dist = 1;
	camera->aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	camera->viewport_width = 2 * tan(fov * M_PI / 360);
	camera->viewport_height = camera->viewport_width / camera->aspect_ratio;
	camera->u = vec3_unit(vec3_cross(camera->orientation, (t_vec3){0, 1, 0}));
	camera->v = vec3_cross(camera->u, camera->orientation);
	camera->horizontal = vec3_scale(camera->u,
			camera->focus_dist * camera->viewport_width);
	camera->vertical = vec3_scale(camera->v,
			camera->focus_dist * camera->viewport_height);
	camera->lower_left = vec3_add(
			vec3_sub(camera->origin,
				vec3_scale(vec3_add(camera->horizontal, camera->vertical),
					0.5)),
			vec3_scale(camera->orientation, camera->focus_dist));
}

bool	parse_camera(t_scene *scene, char **line)
{
	const int	length = arrlen(line);
	double		fov;

	if (scene->camera.exists)
		return (complain_bool(DOUBLE_CAMERA));
	if (length != 4
		|| !parse_coord(line[1], &scene->camera.origin)
		|| !parse_normalized_vector(line[2], &scene->camera.orientation)
		|| !ft_atod_range(line[3], &fov, 0, 180))
		return (complain_bool(ERROR_CAMERA));
	if (fov == 0 || fov == 180)
		return (complain_bool(FOV_ERROR));
	define_camera(&scene->camera, fov);
	return (true);
}

bool	parse_light(t_scene *scene, char **line)
{
	const int	length = arrlen(line);

	if (scene->light.exists)
		return (complain_bool(DOUBLE_LIGHT));
	if (length != 4
		|| !parse_coord(line[1], &scene->light.coord)
		|| !ft_atod_range(line[2], &scene->light.brightness, 0, 1)
		|| !parse_color(line[3], &scene->light.color))
		return (complain_bool(ERROR_LIGHT));
	scene->light.exists = true;
	scene->light.color = vec3_scale(scene->light.color,
			scene->light.brightness / 255);
	return (true);
}
