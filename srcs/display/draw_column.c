#include "cub3d.h"

static void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	mlx->addr[mlx->line_length * y + mlx->bytes_per_pixel * x] = color;
}

static void	set_draw_limits(t_column *column, double half_line_height)
{
	static double	middle_height = (WINDOW_HEIGHT - 1) / 2;

	column->draw_start = middle_height - half_line_height;
	if (column->draw_start < 0)
		column->draw_start = 0;
	column->draw_end = middle_height + half_line_height;
	if (column->draw_end > WINDOW_HEIGHT - 1)
		column->draw_end = WINDOW_HEIGHT - 1;
}

static int	get_color(t_data *data, t_dda *dda, int y, int draw_start, int draw_end, double *tex_pos, double step)
{
	unsigned char	*pixel_addr;
	int				tex_y;
	int				color;

	if (y < draw_start)
		return (data->infos.ceil);
	if (y > draw_end)
		return (data->infos.floor);
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

void	draw_column(t_data *data, t_dda *dda, int x)
{
	t_column	column;
	double		step;
	double		tex_pos;
	int			y;
	int			color;

	set_draw_limits(&column, dda->half_line_height);
	step = (double)dda->texture.height / dda->line_height;
	tex_pos = (column.draw_start - WINDOW_HEIGHT / 2 + dda->half_line_height) * step;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		color = get_color(data, dda, y, column.draw_start, column.draw_end, &tex_pos, step);
		pixel_put(&data->mlx, x, y, color);
		++y;
	}
}
