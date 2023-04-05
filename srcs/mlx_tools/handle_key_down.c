#include "cub3d.h"

int	handle_key_down(int keycode, t_data *data)
{
	t_vec2	new_pos;

	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Up)
	{
		new_pos = vec2_add(data->player.pos,
				vec2_scale(data->player.dir, MOVEMENT));
		if (new_pos.x >= 0 && new_pos.x < data->map.width
			&& new_pos.y >= 0 && new_pos.y < data->map.height)
			data->player.pos = new_pos;
	}
	return (EXIT_SUCCESS);
}
