#include "cub3d.h"

int	handle_key_down(int keycode, t_data *data)
{
	const t_vec2	scaled_dir = vec2_scale(data->player.dir, SPEED);
	t_vec2			new_pos;
	double			turn;

	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Up || keycode == XK_Down)
	{
		if (keycode == XK_Up)
			new_pos = vec2_add(data->player.pos, scaled_dir);
		else
			new_pos = vec2_sub(data->player.pos, scaled_dir);
		if (new_pos.x >= 0 && new_pos.x < data->map.width
			&& new_pos.y >= 0 && new_pos.y < data->map.height)
			data->player.pos = new_pos;
	}
	else if (keycode == XK_Left || keycode == XK_Right)
	{
		if (keycode == XK_Left)
			turn = -TURN;
		else
			turn = TURN;
		data->player.dir = vec2_rotate(data->player.dir, turn);
		data->camera = vec2_rotate(data->camera, turn);
	}
	return (EXIT_SUCCESS);
}
