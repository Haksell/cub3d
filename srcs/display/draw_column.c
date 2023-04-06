#include "cub3d.h"

static void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	mlx->addr[mlx->line_length * y + mlx->bytes_per_pixel * x] = color;
}

static int	get_color(int y, int draw_start, int draw_end, t_data *data, double *tex_pos, t_dda *dda, double step)
{
	int	pixel_index;
	int	tex_y;
	int	color;
	int	red;
	int	green;
	int	blue;

	if (y < draw_start)
		return (data->infos.ceil);
	if (y > draw_end)
		return (data->infos.floor);
	tex_y = clamp((int)*tex_pos, 0, dda->texture.height - 1);
	*tex_pos += step;
	pixel_index = tex_y * dda->texture.size_line + dda->tex_x * dda->texture.bytes_per_pixel;
	red = dda->texture.addr[pixel_index + 2];
	green = dda->texture.addr[pixel_index + 1];
	blue = dda->texture.addr[pixel_index + 0];
	color = red << 16 | green << 8 | blue;
	if (dda->is_vertical)
		color = (color & 0xfefefe) >> 1;
	return (color);
}

void	draw_column(t_data *data, t_dda *dda, int x)
{
	double	step;
	double	tex_pos;
	int		draw_start;
	int		draw_end;
	int		y;
	int		color;

	draw_start = (WINDOW_HEIGHT - 1) / 2 - dda->half_line_height;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (WINDOW_HEIGHT - 1) / 2 + dda->half_line_height;
	if (draw_end > WINDOW_HEIGHT - 1)
		draw_end = WINDOW_HEIGHT - 1;
	step = (double)dda->texture.height / dda->line_height;
	tex_pos = (draw_start - WINDOW_HEIGHT / 2 + dda->half_line_height) * step;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		color = get_color(y, draw_start, draw_end, data, &tex_pos, dda, step);
		pixel_put(&data->mlx, x, y, color);
		++y;
	}
}