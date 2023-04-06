#include "cub3d.h"

static void	set_step_and_side_dist(t_dda *dda, t_vec2 *pos)
{
	if (dda->ray_dir.x < 0)
	{
		dda->step_x = -1;
		dda->side_dist.x = (pos->x - dda->map_x) * dda->delta_dist.x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist.x = (dda->map_x + 1 - pos->x) * dda->delta_dist.x;
	}
	if (dda->ray_dir.y < 0)
	{
		dda->step_y = -1;
		dda->side_dist.y = (pos->y - dda->map_y) * dda->delta_dist.y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist.y = (dda->map_y + 1 - pos->y) * dda->delta_dist.y;
	}
}

static void	init_dda(t_data *data, t_dda *dda, int x)
{
	dda->camera_x = -(2 * x / ((double)WINDOW_WIDTH - 1) - 1);
	dda->ray_dir.x = data->player.dir.x + data->camera.x * dda->camera_x;
	dda->ray_dir.y = data->player.dir.y + data->camera.y * dda->camera_x;
	dda->map_x = (int)data->player.pos.x;
	dda->map_y = (int)data->player.pos.y;
	dda->delta_dist.x = fabs(1.0 / dda->ray_dir.x);
	dda->delta_dist.y = fabs(1.0 / dda->ray_dir.y);
	set_step_and_side_dist(dda, &data->player.pos);
}

static void	execute_dda(t_data *data, t_dda *dda)
{
	while (true)
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->delta_dist.x;
			dda->map_x += dda->step_x;
			dda->is_vertical = false;
		}
		else
		{
			dda->side_dist.y += dda->delta_dist.y;
			dda->map_y += dda->step_y;
			dda->is_vertical = true;
		}
		if (dda->map_x < 0 || dda->map_x >= data->map.width
			|| dda->map_y < 0 || dda->map_y >= data->map.height
			|| data->map.grid[(int)dda->map_y][(int)dda->map_x] == '1')
			break ;
	}
}

static t_texture	get_texture(t_textures *textures, t_dda *dda)
{
	if (dda->is_vertical)
	{
		if (dda->ray_dir.y < 0)
			return (textures->south);
		else
			return (textures->north);
	}
	else
	{
		if (dda->ray_dir.x > 0)
			return (textures->west);
		else
			return (textures->east);
	}
}

static void	terminate_dda(t_data *data, t_dda *dda)
{
	double	perp_wall_dist;

	if (dda->is_vertical)
	{
		perp_wall_dist = dda->side_dist.y - dda->delta_dist.y;
		dda->wall_x = data->player.pos.x + perp_wall_dist * dda->ray_dir.x;
	}
	else
	{
		perp_wall_dist = dda->side_dist.x - dda->delta_dist.x;
		dda->wall_x = data->player.pos.y + perp_wall_dist * dda->ray_dir.y;
	}
	dda->wall_x -= floor(dda->wall_x);
	dda->line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
	dda->half_line_height = dda->line_height >> 1;
	dda->texture = get_texture(&data->textures, dda);
	dda->tex_x = (int)(dda->wall_x * dda->texture.width);
	if ((dda->is_vertical && dda->ray_dir.y < 0)
		|| (!dda->is_vertical && dda->ray_dir.x > 0))
		dda->tex_x = dda->texture.width - dda->tex_x - 1;
}

static void	render_column(t_data *data, int x)
{
	t_dda	dda;

	init_dda(data, &dda, x);
	execute_dda(data, &dda);
	terminate_dda(data, &dda);
	draw_column(data, x, &dda);
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
