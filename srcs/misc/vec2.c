/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:09:08 by axbrisse          #+#    #+#             */
/*   Updated: 2023/05/07 09:09:08 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	vec2_add(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x + v2.x, v1.y + v2.y});
}

t_vec2	vec2_scale(t_vec2 v, double t)
{
	return ((t_vec2){v.x * t, v.y * t});
}

t_vec2	vec2_rotate(t_vec2 v, double angle)
{
	const double	length = sqrt(v.x * v.x + v.y * v.y);

	angle += atan2(v.y, v.x);
	return ((t_vec2){length * cos(angle), length * sin(angle)});
}
