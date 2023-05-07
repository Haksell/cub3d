#include "cub3d.h"

double	vec2_dot(t_vec2 v1, t_vec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

t_vec2	vec2_mul(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x * v2.x, v1.y * v2.y});
}

static double	vec2_length_squared(t_vec2 v)
{
	return (vec2_dot(v, v));
}

static double	vec2_length(t_vec2 v)
{
	return (sqrt(vec2_length_squared(v)));
}

t_vec2	vec2_rotate(t_vec2 v, double angle)
{
	const double	length = vec2_length(v);

	angle += atan2(v.y, v.x);
	return ((t_vec2){length * cos(angle), length * sin(angle)});
}
