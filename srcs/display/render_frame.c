#include "cub3d.h"

static void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	mlx->addr[mlx->line_length * y + mlx->bytes_per_pixel * x] = color;
}

static void	draw_vertical_line(t_data *data, int x, int line_height, int color)
{
	int	draw_start;
	int	draw_end;
	int	y;

	draw_start = (WINDOW_HEIGHT - 1) / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (WINDOW_HEIGHT - 1) / 2 + line_height / 2;
	if (draw_end > WINDOW_HEIGHT - 1)
		draw_end = WINDOW_HEIGHT - 1;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < draw_start)
			pixel_put(&data->mlx, x, y, data->infos.ceil);
		else if (y > draw_end)
			pixel_put(&data->mlx, x, y, data->infos.floor);
		else
			pixel_put(&data->mlx, x, y, color);
		++y;
	}
}

int	render_frame(t_data *data)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	bool	is_vertical;
	int		line_height;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		x;
	int		color;

	x = 0;
	// printf("data->frame=%d\n", data->frame);
	// printf("pos.x=%.3lf\n", data->player.pos.x);
	// printf("pos.y=%.3lf\n", data->player.pos.y);
	// printf("dir.x=%.3lf\n", data->player.dir.x);
	// printf("dir.y=%.3lf\n", data->player.dir.y);
	// printf("\n");
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
		{
			if (step_y < 0)
				color = 0x0000ff;
			else
				color = 0xff0000;
		}
		else
		{
			if (step_x < 0)
				color = 0x00ff00;
			else
				color = 0x808080;
		}
		draw_vertical_line(data, x, line_height, color);
		++x;
	}
	++data->frame;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (EXIT_SUCCESS);
}
