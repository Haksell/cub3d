#include "cub3d.h"

static int	get_int_component(double x)
{
	return ((int)(255.9999 * x));
}

static void	pixel_put(t_mlx *mlx, int x, int y, t_vec3 color)
{
	const int	r = get_int_component(color.x);
	const int	g = get_int_component(color.y);
	const int	b = get_int_component(color.z);
	const int	offset = mlx->line_length * y + mlx->bytes_per_pixel * x;

	mlx->addr[offset] = r << 16 | g << 8 | b;
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
			pixel_put(&data->mlx, x, y, (t_vec3){0.5, 0.8, 1});
			++x;
		}
		++y;
	}
	++data->frame;
	ft_printf("data->frame=%d\n", data->frame);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (EXIT_SUCCESS);
}
