#include "cub3d.h"

t_vec2	vec2_negate(t_vec2 v)
{
	return ((t_vec2){-v.x, -v.y});
}

t_vec2	vec2_add(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x + v2.x, v1.y + v2.y});
}

t_vec2	vec2_sub(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x - v2.x, v1.y - v2.y});
}

t_vec2	vec2_scale(t_vec2 v, double t)
{
	return ((t_vec2){v.x * t, v.y * t});
}

t_vec2	vec2_div(t_vec2 v, double t)
{
	const double	u = 1 / t;

	return ((t_vec2){v.x * u, v.y * u});
}
