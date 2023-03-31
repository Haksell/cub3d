#include "minirt.h"

static int	get_int_component(double x)
{
	return (clamp((int)(255.9999 * sqrt(x)), 0, 255));
}

static void	pixel_put(t_mlx *mlx, int x, int y, t_vec3 color)
{
	const int	r = get_int_component(color.x);
	const int	g = get_int_component(color.y);
	const int	b = get_int_component(color.z);
	const int	offset = mlx->line_length * y + mlx->bytes_per_pixel * x;

	mlx->addr[offset] = r << 16 | g << 8 | b;
}

static void	render_pixel(t_data *data, int y, int x)
{
	t_ray	ray;
	double	u;
	double	v;

	u = (x + get_random_double()) / (WINDOW_WIDTH - 1);
	v = (WINDOW_HEIGHT - y - 1 + get_random_double()) / (WINDOW_HEIGHT - 1);
	ray = get_ray(&data->scene.camera, u, v);
	data->pixels[y][x] = vec3_div(
			vec3_add(
				vec3_scale(data->pixels[y][x], data->frame),
				ray_color(ray, &data->scene, MAX_DEPTH)),
			data->frame + 1);
	pixel_put(&data->mlx, x, y, data->pixels[y][x]);
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
			render_pixel(data, y, x);
			++x;
		}
		++y;
	}
	++data->frame;
	ft_printf("data->frame=%d\n", data->frame);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (EXIT_SUCCESS);
}
