#include "cub3d.h"

static void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	mlx->addr[mlx->line_length * y + mlx->bytes_per_pixel * x] = color;
}

int	render_frame(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_put(&data->mlx, x, y, 0x80CCFF);
			++x;
		}
		++y;
	}
	++data->frame;
	printf("data->frame=%d\n", data->frame);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (EXIT_SUCCESS);
}
