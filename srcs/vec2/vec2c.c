#include "cub3d.h"

double	vec2_length_squared(t_vec2 v)
{
	return (vec2_dot(v, v));
}

double	vec2_length(t_vec2 v)
{
	return (sqrt(vec2_length_squared(v)));
}

t_vec2	vec2_unit(t_vec2 v)
{
	if (v.x == 0 && v.y == 0)
		return (v);
	return (vec2_div(v, vec2_length(v)));
}

double	vec2_dist_squared(t_vec2 v1, t_vec2 v2)
{
	return (vec2_length_squared(vec2_sub(v1, v2)));
}

double	vec2_dist(t_vec2 v1, t_vec2 v2)
{
	return (vec2_length(vec2_sub(v1, v2)));
}
