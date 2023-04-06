#include "cub3d.h"

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->infos.floor = -1;
	data->infos.ceil = -1;
	data->player.pos.x = -1;
	data->player.pos.y = -1;
	data->mov.forward = false;
	data->mov.backward = false;
	data->mov.right = false;
	data->mov.left = false;
	data->mov.turn_l = false;
	data->mov.turn_r = false;
}

