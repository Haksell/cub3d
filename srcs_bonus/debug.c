#include "cub3d.h"

void	display_map(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		ft_putendl_fd(map->grid[y], STDOUT_FILENO);
		++y;
	}
}
