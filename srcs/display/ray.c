#include "minirt.h"

t_ray	get_ray(const t_camera *camera, double s, double t)
{
	const t_vec3	rd = vec3_scale(get_random_in_unit_disk(),
			camera->lens_radius);
	const t_vec3	offset = vec3_add(
			vec3_scale(camera->u, rd.x),
			vec3_scale(camera->v, rd.y));
	const t_vec3	moved_camera = vec3_add(camera->origin, offset);
	const t_vec3	direction = vec3_add(
			vec3_add(
				vec3_scale(camera->horizontal, s),
				vec3_scale(camera->vertical, t)),
			vec3_sub(camera->lower_left, moved_camera));

	return ((t_ray){moved_camera, direction});
}

t_vec3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}

t_vec3	ray_color(t_ray ray, t_scene *scene, int depth)
{
	static t_vec3	black = (t_vec3){0, 0, 0};
	t_vec3			attenuation;
	t_hit			hit;
	t_ray			scattered;
	t_vec3			light_color;

	if (depth <= 0)
		return (black);
	if (hit_world(&hit, scene, &ray, &(t_interval){SHADOW_ACNE_FIX, INFINITY}))
	{
		light_color = get_light_impact(scene, &hit, ray);
		if (scatter(ray, hit, &attenuation, &scattered))
			return (vec3_add(light_color,
					vec3_mul(attenuation,
						ray_color(scattered, scene, depth - 1))));
		return (light_color);
	}
	return (scene->ambient.color);
}

void	set_face_normal(t_hit *hit, t_ray *ray, t_vec3 *outward_normal)
{
	hit->front_face = vec3_dot(ray->direction, *outward_normal) < 0;
	if (hit->front_face)
		hit->normal = *outward_normal;
	else
		hit->normal = vec3_negate(*outward_normal);
}
