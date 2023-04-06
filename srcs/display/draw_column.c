#include "cub3d.h"

static void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	mlx->addr[mlx->line_length * y + mlx->bytes_per_pixel * x] = color;
}

void	draw_column(t_data *data, int x, t_dda *dda)
{
	double	step;
	double	tex_pos;
	int		pixel_index;
	int		tex_y;
	int		draw_start;
	int		draw_end;
	int		y;
	int		color;
	int		red;
	int		green;
	int		blue;

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
		if (y < draw_start)
			pixel_put(&data->mlx, x, y, data->infos.ceil);
		else if (y > draw_end)
			pixel_put(&data->mlx, x, y, data->infos.floor);
		else
		{
			tex_y = clamp((int)tex_pos, 0, dda->texture.height - 1);
			tex_pos += step;
			pixel_index = tex_y * dda->texture.size_line + dda->tex_x * dda->texture.bytes_per_pixel;
			red = dda->texture.addr[pixel_index + 2];
			green = dda->texture.addr[pixel_index + 1];
			blue = dda->texture.addr[pixel_index + 0];
			color = red << 16 | green << 8 | blue;
			if (dda->is_vertical)
				color = (color & 0xfefefe) >> 1;
			pixel_put(&data->mlx, x, y, color);
		}
		++y;
	}
}
