#include "minirt.h"

double	reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 *= r0;
	return (r0 + (1 - r0) * pow(1 - cosine, 5));
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_scale(n, 2 * vec3_dot(v, n))));
}

t_vec3	refract(t_vec3 v, t_vec3 n, double ir)
{
	const double	cos_theta = fmin(-vec3_dot(v, n), 1);
	const t_vec3	perpendicular = vec3_scale(
			vec3_add(v, vec3_scale(n, cos_theta)), ir);
	const t_vec3	parallel = vec3_scale(
			n, -sqrt(fabs(1 - vec3_length_squared(perpendicular))));

	return (vec3_add(perpendicular, parallel));
}

t_vec3	get_light_impact(t_scene *scene, t_hit *hit, t_ray ray)
{
	t_vec3	light_amt;
	//t_vec3	specular_color;
	t_vec3	light_dir;
	t_ray	shadow_ray;
	float	light_distance2;
	float	ldotn;
	t_hit	shadow_hit;
	t_interval	inter;

	if (vec3_dot(ray.direction, hit->normal) < 0)
		shadow_ray.origin = vec3_add(hit->point, hit->normal);
	else
		shadow_ray.origin = vec3_sub(hit->point, hit->normal);
	//if multiple lights, do a loop
	light_dir = vec3_sub(scene->light.coord, hit->point);
	light_distance2 = vec3_length_squared(light_dir);
	light_dir = vec3_unit(light_dir);
	ldotn = fmax(0.0, vec3_dot(light_dir, hit->normal));
	inter = (t_interval){SHADOW_ACNE_FIX, INFINITY};
	bool check = hit_world(&shadow_hit, scene, &shadow_ray, &inter);
	check = check && (inter.max * inter.max < light_distance2);
	//return (!check);
	light_amt = vec3_scale(vec3_scale(scene->light.color, 1 - check), ldotn);
	return (light_amt);
}