#include "cub3d.h"

static void	free_image(void *mlx, void *img)
{
	if (img != NULL)
		mlx_destroy_image(mlx, img);
}

void	free_data(t_data *data)
{
	if (data->mlx.mlx != NULL)
	{
		free_image(data->mlx.mlx, data->textures.north.img);
		free_image(data->mlx.mlx, data->textures.east.img);
		free_image(data->mlx.mlx, data->textures.south.img);
		free_image(data->mlx.mlx, data->textures.west.img);
		free_image(data->mlx.mlx, data->mlx.img);
		if (data->mlx.win != NULL)
			mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
	free(data->infos.path_north_texture);
	free(data->infos.path_east_texture);
	free(data->infos.path_south_texture);
	free(data->infos.path_west_texture);
	ft_free_double((void ***)&data->map.grid);
}

int	close_window(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
