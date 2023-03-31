#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (!init_pixels(&data)
		|| !parse_map(&data.map, argc, argv)
		|| !init_minilibx(&data.mlx, argv[1]))
		return (free_data(&data), EXIT_FAILURE);
	mlx_hook(data.mlx.win, DestroyNotify, NoEventMask, close_window, &data);
	mlx_hook(data.mlx.win, KeyPress, KeyPressMask, handle_key_down, &data);
	mlx_loop_hook(data.mlx.mlx, &render_frame, &data);
	mlx_loop(data.mlx.mlx);
	return (EXIT_SUCCESS);
}
