#include "minirt.h"

t_vec3	get_random_in_unit_disk(void)
{
	t_vec3	v;
	double	length;

	v.z = 0;
	while (true)
	{
		v.x = get_random_double_range(-1, 1);
		v.y = get_random_double_range(-1, 1);
		length = vec3_length_squared(v);
		if (0 < length && length < 1)
			return (v);
	}
}

t_vec3	get_random_in_unit_sphere(void)
{
	t_vec3	v;
	double	length;

	while (true)
	{
		v.x = get_random_double_range(-1, 1);
		v.y = get_random_double_range(-1, 1);
		v.z = get_random_double_range(-1, 1);
		length = vec3_length_squared(v);
		if (0 < length && length < 1)
			return (v);
	}
}

t_vec3	get_random_unit_vector(void)
{
	return (vec3_unit(get_random_in_unit_sphere()));
}

t_vec3	get_random_in_hemisphere(t_vec3 normal)
{
	t_vec3	v;

	v = get_random_in_unit_sphere();
	if (vec3_dot(v, normal) > 0)
		return (v);
	else
		return (vec3_negate(v));
}
