/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:09:29 by axbrisse          #+#    #+#             */
/*   Updated: 2023/05/07 09:09:30 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir_and_camera(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player.dir = (t_vec2){0, -1};
		data->camera = (t_vec2){-CAMERA_FOV, 0};
	}
	else if (c == 'E')
	{
		data->player.dir = (t_vec2){1, 0};
		data->camera = (t_vec2){0, -CAMERA_FOV};
	}
	else if (c == 'S')
	{
		data->player.dir = (t_vec2){0, 1};
		data->camera = (t_vec2){CAMERA_FOV, 0};
	}
	else
	{
		data->player.dir = (t_vec2){-1, 0};
		data->camera = (t_vec2){0, CAMERA_FOV};
	}
}

static bool	valid_character(t_data *data, int y, int x)
{
	const char	c = data->map.grid[y][x];

	if (ft_strchr(MAP_CHARACTERS, c) == NULL)
	{
		if (ft_strchr(PLAYER_CHARACTERS, c) == NULL)
			return (complain_bool(ERROR_INVALID_CHAR));
		else if (data->player.pos.x != -1)
			return (complain_bool(ERROR_MULTIPLAYER));
		else
		{
			data->player.pos = (t_vec2){x + 0.5, y + 0.5};
			data->map.grid[y][x] = '0';
			set_dir_and_camera(data, c);
		}
	}
	return (true);
}

bool	valid_characters(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (!valid_character(data, y, x))
				return (false);
			++x;
		}
		++y;
	}
	if (data->player.pos.x == -1)
		return (complain_bool(ERROR_NO_PLAYER));
	return (true);
}
