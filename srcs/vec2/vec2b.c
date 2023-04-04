#include "cub3d.h"

double	vec2_dot(t_vec2 v1, t_vec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

t_vec2	vec2_mul(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x * v2.x, v1.y * v2.y});
}
