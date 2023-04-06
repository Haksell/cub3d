#include "cub3d.h"

static void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	mlx->addr[mlx->line_length * y + mlx->bytes_per_pixel * x] = color;
}

static void	draw_column(t_data *data, int x, int tex_x, int line_height, bool is_vertical, t_texture texture)
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

	draw_start = (WINDOW_HEIGHT - 1) / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (WINDOW_HEIGHT - 1) / 2 + line_height / 2;
	if (draw_end > WINDOW_HEIGHT - 1)
		draw_end = WINDOW_HEIGHT - 1;
	step = (double)texture.height / line_height;
	tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < draw_start)
			pixel_put(&data->mlx, x, y, data->infos.ceil);
		else if (y > draw_end)
			pixel_put(&data->mlx, x, y, data->infos.floor);
		else
		{
			tex_y = clamp((int)tex_pos, 0, texture.height - 1);
			tex_pos += step;
			pixel_index = tex_y * texture.size_line + tex_x * texture.bytes_per_pixel;
			red = texture.addr[pixel_index + 2];
			green = texture.addr[pixel_index + 1];
			blue = texture.addr[pixel_index + 0];
			color = red << 16 | green << 8 | blue;
			if (is_vertical)
				color = (color & 0xfefefe) >> 1;
			pixel_put(&data->mlx, x, y, color);
		}
		++y;
	}
}

static void	render_column(t_data *data, int x)
{
	t_dda		dda;
	t_texture	texture;
	double		camera_x;
	double		wall_x;
	double		perp_wall_dist;
	bool		is_vertical;
	int			tex_x;
	int			line_height;

	camera_x = -(2 * x / ((double)WINDOW_WIDTH - 1) - 1);
	dda.ray_dir.x = data->player.dir.x + data->camera.x * camera_x;
	dda.ray_dir.y = data->player.dir.y + data->camera.y * camera_x;
	dda.map_x = (int)data->player.pos.x;
	dda.map_y = (int)data->player.pos.y;
	dda.delta_dist.x = fabs(1.0 / dda.ray_dir.x);
	dda.delta_dist.y = fabs(1.0 / dda.ray_dir.y);
	if (dda.ray_dir.x < 0)
	{
		dda.step.x = -1;
		dda.side_dist.x = (data->player.pos.x - dda.map_x) * dda.delta_dist.x;
	}
	else
	{
		dda.step.x = 1;
		dda.side_dist.x = (dda.map_x + 1 - data->player.pos.x) * dda.delta_dist.x;
	}
	if (dda.ray_dir.y < 0)
	{
		dda.step.y = -1;
		dda.side_dist.y = (data->player.pos.y - dda.map_y) * dda.delta_dist.y;
	}
	else
	{
		dda.step.y = 1;
		dda.side_dist.y = (dda.map_y + 1 - data->player.pos.y) * dda.delta_dist.y;
	}
	while (true)
	{
		if (dda.side_dist.x < dda.side_dist.y)
		{
			dda.side_dist.x += dda.delta_dist.x;
			dda.map_x += dda.step.x;
			is_vertical = false;
		}
		else
		{
			dda.side_dist.y += dda.delta_dist.y;
			dda.map_y += dda.step.y;
			is_vertical = true;
		}
		if (dda.map_x < 0 || dda.map_x >= data->map.width
			|| dda.map_y < 0 || dda.map_y >= data->map.height
			|| data->map.grid[(int)dda.map_y][(int)dda.map_x] == '1')
			break ;
	}
	if (is_vertical)
		perp_wall_dist = dda.side_dist.y - dda.delta_dist.y;
	else
		perp_wall_dist = dda.side_dist.x - dda.delta_dist.x;
	line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
	if (is_vertical)
		wall_x = data->player.pos.x + perp_wall_dist * dda.ray_dir.x;
	else
		wall_x = data->player.pos.y + perp_wall_dist * dda.ray_dir.y;
	if (is_vertical)
	{
		texture = data->textures.north;
		if (dda.ray_dir.y < 0)
			texture = data->textures.south;
	}
	else
	{
		texture = data->textures.east;
		if (dda.ray_dir.x > 0)
			texture = data->textures.west;
	}
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture.width);
	if ((is_vertical && dda.ray_dir.y < 0) || (!is_vertical && dda.ray_dir.x > 0))
		tex_x = texture.width - tex_x - 1;
	draw_column(data, x, tex_x, line_height, is_vertical, texture);
	++x;
}

int	render_frame(t_data *data)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		render_column(data, x);
		++x;
	}
	++data->frame;
	printf("%d\n", data->frame);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (EXIT_SUCCESS);
}
