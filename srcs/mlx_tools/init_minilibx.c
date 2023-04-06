#include "cub3d.h"

static bool	load_texture(void *mlx, char *path, t_texture *texture)
{
	int	_;

	texture->img = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	if (texture->img == NULL)
		return (complain_bool(ERROR_TEXTURES));
	texture->addr = (unsigned int *)mlx_get_data_addr(texture->img,
			&texture->bytes_per_pixel, &texture->size_line, &_);
	texture->size_line >>= 2;
	texture->bytes_per_pixel >>= 5;
	if (texture->addr == NULL)
		return (complain_bool(ERROR_TEXTURES));
	return (true);
}

static bool	load_textures(t_data *data)
{
	return (load_texture(data->mlx.mlx,
			data->infos.path_north_texture,
			&data->textures.north)
		&& load_texture(data->mlx.mlx,
			data->infos.path_east_texture,
			&data->textures.east)
		&& load_texture(data->mlx.mlx,
			data->infos.path_south_texture,
			&data->textures.south)
		&& load_texture(data->mlx.mlx,
			data->infos.path_west_texture,
			&data->textures.west));
}

bool	init_minilibx(t_data *data, char *window_title)
{
	int	_;

	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		return (complain_bool(ERROR_MLX));
	if (!load_textures(data))
		return (false);
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
