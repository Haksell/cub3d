#include "cub3d.h"

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->infos.floor = -1;
	data->infos.ceil = -1;
}