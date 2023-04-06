#include "cub3d.h"

static void	handle_movement(int keycode, t_data *data)
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
	if (new_pos.x >= 0 && new_pos.x < data->map.width
		&& new_pos.y >= 0 && new_pos.y < data->map.height)
		data->player.pos = new_pos;
}

static void	handle_rotation(int keycode, t_data *data)
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
	else if (keycode == XK_W || keycode == XK_w
		|| keycode == XK_D || keycode == XK_d
		|| keycode == XK_S || keycode == XK_s
		|| keycode == XK_A || keycode == XK_a)
		handle_movement(keycode, data);
	else if (keycode == XK_Left || keycode == XK_Right)
		handle_rotation(keycode, data);
	return (EXIT_SUCCESS);
}
