#include "cub3d.h"

static void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	mlx->addr[mlx->line_length * y + mlx->bytes_per_pixel * x] = color;
}

static void	draw_vertical_line(t_data *data, int x, int tex_x, int line_height, bool is_vertical)
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
	step = (double)data->textures.east.height / line_height;
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
			tex_y = clamp((int)tex_pos, 0, data->textures.east.height - 1);
			tex_pos += step;
			pixel_index = (tex_y * data->textures.east.size_line) + (tex_x * (data->textures.east.bits_per_pixel / 8));
			red = (unsigned int)data->textures.east.data[pixel_index + 2];
			green = (unsigned char)data->textures.east.data[pixel_index + 1];
			blue = (unsigned char)data->textures.east.data[pixel_index + 0];
			color = red << 16 | green << 8 | blue;
			if (is_vertical)
				color = (color & 0xfefefe) >> 1;
			pixel_put(&data->mlx, x, y, color);
		}
		++y;
	}
}

int	render_frame(t_data *data)
{
	double	camera_x;
	double	wall_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	bool	is_vertical;
	int		tex_x;
	int		line_height;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		camera_x = -(2 * x / ((double)WINDOW_WIDTH - 1) - 1);
		ray_dir_x = data->player.dir.x + data->camera.x * camera_x;
		ray_dir_y = data->player.dir.y + data->camera.y * camera_x;
		map_x = (int)data->player.pos.x;
		map_y = (int)data->player.pos.y;
		delta_dist_x = fabs(1.0 / ray_dir_x);
		delta_dist_y = fabs(1.0 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player.pos.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1 - data->player.pos.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player.pos.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1 - data->player.pos.y) * delta_dist_y;
		}
		while (true)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				is_vertical = false;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				is_vertical = true;
			}
			if (map_x < 0 || map_x >= data->map.width
				|| map_y < 0 || map_y >= data->map.height
				|| data->map.grid[map_y][map_x] == '1')
				break ;
		}
		if (is_vertical)
			perp_wall_dist = side_dist_y - delta_dist_y;
		else
			perp_wall_dist = side_dist_x - delta_dist_x;
		line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
		if (is_vertical)
			wall_x = data->player.pos.x + perp_wall_dist * ray_dir_x;
		else
			wall_x = data->player.pos.y + perp_wall_dist * ray_dir_y;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * 64); // TODO texture width
		// TODO inverse texture
		draw_vertical_line(data, x, tex_x, line_height, is_vertical);
		++x;
	}
	++data->frame;
	printf("%d\n", data->frame);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (EXIT_SUCCESS);
}
