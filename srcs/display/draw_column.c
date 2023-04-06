#include "cub3d.h"

static void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	mlx->addr[mlx->line_length * y + mlx->bytes_per_pixel * x] = color;
}

static void	draw_unicolor(t_mlx *mlx, int x, int color, t_interval interval)
{
	int	y;

	y = interval.start;
	while (y <= interval.end)
	{
		pixel_put(mlx, x, y, color);
		++y;
	}
}

static int	get_color(t_dda *dda, double *tex_pos, double step)
{
	unsigned char	*pixel_addr;
	int				tex_y;
	int				color;

	tex_y = clamp((int)*tex_pos, 0, dda->texture.height - 1);
	*tex_pos += step;
	pixel_addr = dda->texture.addr
		+ tex_y * dda->texture.size_line
		+ dda->tex_x * dda->texture.bytes_per_pixel;
	color = pixel_addr[2] << 16 | pixel_addr[1] << 8 | pixel_addr[0];
	if (dda->is_vertical)
		color = (color & 0xfefefe) >> 1;
	return (color);
}

static void	draw_sprite(t_data *data, t_dda *dda, int x, t_interval interval)
{
	double	step;
	double	tex_pos;
	int		y;

	step = (double)dda->texture.height / dda->line_height;
	tex_pos = interval.start - WINDOW_HEIGHT / 2 + dda->half_line_height;
	tex_pos *= step;
	y = interval.start;
	while (y <= interval.end)
	{
		pixel_put(&data->mlx, x, y, get_color(dda, &tex_pos, step));
		++y;
	}
}

void	draw_column(t_data *data, t_dda *dda, int x)
{
	static double	middle_height = (WINDOW_HEIGHT - 1) / 2;
	t_interval		interval;

	interval.start = middle_height - dda->half_line_height;
	if (interval.start < 0)
		interval.start = 0;
	interval.end = middle_height + dda->half_line_height;
	if (interval.end > WINDOW_HEIGHT - 1)
		interval.end = WINDOW_HEIGHT - 1;
	draw_unicolor(&data->mlx, x, data->infos.ceil,
		(t_interval){0, interval.start - 1});
	draw_sprite(data, dda, x, interval);
	draw_unicolor(&data->mlx, x, data->infos.floor,
		(t_interval){interval.end + 1, WINDOW_HEIGHT - 1});
}
