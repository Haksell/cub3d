#include "cub3d.h"

t_vec3	vec3_negate(t_vec3 v)
{
	return ((t_vec3){-v.x, -v.y, -v.z});
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec3	vec3_scale(t_vec3 v, double t)
{
	return ((t_vec3){v.x * t, v.y * t, v.z * t});
}

t_vec3	vec3_div(t_vec3 v, double t)
{
	const double	u = 1 / t;

	return ((t_vec3){v.x * u, v.y * u, v.z * u});
}
