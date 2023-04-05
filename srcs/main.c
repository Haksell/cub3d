#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	if (!parse_file(&data, argc, argv) || !init_minilibx(&data, argv[1]))
		return (free_data(&data), EXIT_FAILURE);
	mlx_hook(data.mlx.win, DestroyNotify, NoEventMask, close_window, &data);
	mlx_hook(data.mlx.win, KeyPress, KeyPressMask, handle_key_press, &data);
	mlx_loop_hook(data.mlx.mlx, &render_frame, &data);
	mlx_loop(data.mlx.mlx);
	return (EXIT_SUCCESS);
}
