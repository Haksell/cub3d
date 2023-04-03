#include "cub3d.h"

static bool	load_textures(t_data *data)
{
	int	_;

	printf("KOKO[%s]\n", data->infos.path_north_texture);
	printf("LOL[%s]\n", data->infos.path_east_texture);
	printf("%s\n", data->infos.path_south_texture);
	printf("%s\n", data->infos.path_west_texture);
	data->textures.north = mlx_xpm_file_to_image(
			data->mlx.mlx, data->infos.path_north_texture, &_, &_);
	data->textures.east = mlx_xpm_file_to_image(
			data->mlx.mlx, data->infos.path_east_texture, &_, &_);
	data->textures.south = mlx_xpm_file_to_image(
			data->mlx.mlx, data->infos.path_south_texture, &_, &_);
	data->textures.west = mlx_xpm_file_to_image(
			data->mlx.mlx, data->infos.path_west_texture, &_, &_);
	return (data->textures.north != NULL
		&& data->textures.east != NULL
		&& data->textures.south != NULL
		&& data->textures.west != NULL);
}

bool	init_minilibx(t_data *data, char *window_title)
{
	int	_;

	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		return (complain_bool(ERROR_MLX));
	if (!load_textures(data))
		return (complain_bool(ERROR_TEXTURES));
	data->mlx.win = mlx_new_window(data->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			window_title);
	if (data->mlx.win == NULL)
		return (complain_bool(ERROR_WINDOW));
	data->mlx.img = mlx_new_image(data->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->mlx.img == NULL)
		return (complain_bool(ERROR_IMAGE));
	data->mlx.addr = (int *)mlx_get_data_addr(data->mlx.img,
			&data->mlx.bytes_per_pixel, &data->mlx.line_length, &_);
	if (data->mlx.addr == NULL)
		return (complain_bool(ERROR_ADDR));
	data->mlx.bytes_per_pixel >>= 5;
	data->mlx.line_length >>= 2;
	return (true);
}
