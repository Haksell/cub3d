#include "cub3d.h"

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	data->player.forward += keycode == XK_w;
	data->player.right -= keycode == XK_a;
	data->player.forward -= keycode == XK_s;
	data->player.right += keycode == XK_d;
	data->player.clockwise += keycode == XK_Right;
	data->player.clockwise -= keycode == XK_Left;
	return (EXIT_SUCCESS);
}

int	handle_key_release(int keycode, t_data *data)
{
	data->player.forward -= keycode == XK_w;
	data->player.right += keycode == XK_a;
	data->player.forward += keycode == XK_s;
	data->player.right -= keycode == XK_d;
	data->player.clockwise -= keycode == XK_Right;
	data->player.clockwise += keycode == XK_Left;
	return (EXIT_SUCCESS);
}
