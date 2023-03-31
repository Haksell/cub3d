#include "cub3d.h"

double	vec3_length_squared(t_vec3 v)
{
	return (vec3_dot(v, v));
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

t_vec3	vec3_unit(t_vec3 v)
{
	return (vec3_div(v, vec3_length(v)));
}

double	vec3_dist_squared(t_vec3 v1, t_vec3 v2)
{
	return (vec3_length_squared(vec3_sub(v1, v2)));
}

double	vec3_dist(t_vec3 v1, t_vec3 v2)
{
	return (vec3_length(vec3_sub(v1, v2)));
}
