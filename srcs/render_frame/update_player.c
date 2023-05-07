/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:09:38 by axbrisse          #+#    #+#             */
/*   Updated: 2023/05/07 09:09:38 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_position(t_data *data)
{
	t_vec2	new_pos;
	int		octant;

	if (data->player.forward == 0 && data->player.right == 0)
		return ;
	if (data->player.forward == 1)
		octant = data->player.right;
	else if (data->player.forward == 0)
		octant = 2 * data->player.right;
	else
		octant = 4 - data->player.right;
	new_pos = vec2_add(data->player.pos, vec2_scale(vec2_rotate(
					data->player.dir, octant * M_PI / 4), SPEED));
	if (new_pos.x >= 0 && new_pos.x < data->map.width
		&& new_pos.y >= 0 && new_pos.y < data->map.height)
		data->player.pos = new_pos;
}

static void	update_direction(t_data *data)
{
	const double	turn = data->player.clockwise * TURN;

	data->player.dir = vec2_rotate(data->player.dir, turn);
	data->camera = vec2_rotate(data->camera, turn);
}

void	update_player(t_data *data)
{
	update_position(data);
	update_direction(data);
}
