#include "cub3d.h"

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x,
	});
}

bool	vec3_near_zero(t_vec3 v)
{
	static double	epsilon = 1e-8;

	return (fabs(v.x) < epsilon && fabs(v.y) < epsilon && fabs(v.z) < epsilon);
}

t_vec3	vec3_mul(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}
