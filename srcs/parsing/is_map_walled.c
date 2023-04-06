#include "cub3d.h"

static bool	is_outside(t_map *map, int y, int x)
{
	return (y < 0 || y >= map->height
		|| x < 0 || x >= map->width
		|| map->grid[y][x] == '.');
}

bool	is_map_walled(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (ft_strchr(NON_WALL_CHARACTERS, map->grid[y][x]) != NULL
				&& (is_outside(map, y - 1, x)
					|| is_outside(map, y, x + 1)
					|| is_outside(map, y + 1, x)
					|| is_outside(map, y, x - 1)))
				return (false);
			++x;
		}
		++y;
	}
	return (true);
}
