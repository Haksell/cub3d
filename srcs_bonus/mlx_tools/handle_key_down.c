#include "cub3d.h"

void	handle_movement(int keycode, t_data *data)
{
	const t_vec2	scaled_dir = vec2_scale(data->player.dir, SPEED);
	t_vec2			rotated_dir;
	t_vec2			new_pos;

	if (keycode == XK_W || keycode == XK_w)
		rotated_dir = scaled_dir;
	else if (keycode == XK_A || keycode == XK_a)
		rotated_dir = (t_vec2){scaled_dir.y, -scaled_dir.x};
	else if (keycode == XK_S || keycode == XK_s)
		rotated_dir = (t_vec2){-scaled_dir.x, -scaled_dir.y};
	else
		rotated_dir = (t_vec2){-scaled_dir.y, scaled_dir.x};
	new_pos = vec2_add(data->player.pos, rotated_dir);
	printf("new_pos.x == [%f] && new_pos.y === [%f]\n", new_pos.x, new_pos.y);
	printf("data->map.grid[%d][%d] ==[%c]\n", (int)new_pos.x, (int)new_pos.y, data->map.grid[(int)new_pos.y][(int)new_pos.y]);
	if (new_pos.x >= 0 && new_pos.x < data->map.width
		&& new_pos.y >= 0 && new_pos.y < data->map.height
		&& data->map.grid[(int)new_pos.y][(int)new_pos.x] != '1')
		data->player.pos = new_pos;
}

void	handle_rotation(int keycode, t_data *data)
{
	double	turn;

	if (keycode == XK_Left)
		turn = -TURN;
	else
		turn = TURN;
	data->player.dir = vec2_rotate(data->player.dir, turn);
	data->camera = vec2_rotate(data->camera, turn);
}

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_W || keycode == XK_w)
		data->mov.forward = true;
	else if (keycode == XK_D || keycode == XK_d)
		data->mov.right = true;
	else if (keycode == XK_S || keycode == XK_s)
		data->mov.backward = true;
	else if (keycode == XK_A || keycode == XK_a)
		data->mov.left = true;
	else if (keycode == XK_Left)
		data->mov.turn_l = true;
	else if (keycode == XK_Right)
		data->mov.turn_r = true;
	return (EXIT_SUCCESS);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == XK_W || keycode == XK_w)
		data->mov.forward = false;
	else if (keycode == XK_D || keycode == XK_d)
		data->mov.right = false;
	else if (keycode == XK_S || keycode == XK_s)
		data->mov.backward = false;
	else if (keycode == XK_A || keycode == XK_a)
		data->mov.left = false;
	else if (keycode == XK_Left)
		data->mov.turn_l = false;
	else if (keycode == XK_Right)
		data->mov.turn_r = false;
	return (EXIT_SUCCESS);
}
