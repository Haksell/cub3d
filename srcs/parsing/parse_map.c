#include "cub3d.h"

static void	get_map_dimensions(t_map *map, char **lines)
{
	int	length;

	map->height = 0;
	while (lines[map->height] != NULL)
	{
		length = ft_strlen(lines[map->height]);
		if (length > map->width)
			map->width = length;
		++map->height;
	}
}

static bool	init_map(t_map *map, char **lines)
{
	int	i;
	int	j;

	get_map_dimensions(map, lines);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (map->grid == NULL)
		return (complain_bool(MALLOC_ERROR));
	i = 0;
	while (lines[i] != NULL)
	{
		map->grid[i] = ft_calloc(map->width + 1, sizeof(char));
		if (map->grid[i] == NULL)
			return (complain_bool(MALLOC_ERROR));
		ft_strlcpy(map->grid[i], lines[i], map->width + 1);
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == ' ' || map->grid[i][j] == '\0')
				map->grid[i][j] = '.';
			++j;
		}
		++i;
	}
	return (true);
}

static bool	valid_character(char c, bool *found_player)
{
	if (ft_strchr(MAP_CHARACTERS, c) == NULL)
	{
		if (ft_strchr(PLAYER_CHARACTERS, c) == NULL)
			return (complain_bool(ERROR_INVALID_CHAR));
		else if (*found_player)
			return (complain_bool(ERROR_MULTIPLAYER));
		else
			*found_player = true;
	}
	return (true);
}

static bool	valid_characters(t_map *map)
{
	bool	found_player;
	int		x;
	int		y;

	found_player = false;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!valid_character(map->grid[y][x], &found_player))
				return (false);
			++x;
		}
		++y;
	}
	if (!found_player)
		return (complain_bool(ERROR_NO_PLAYER));
	return (true);
}

static bool	is_outside(t_map *map, int y, int x)
{
	return (y < 0 || y >= map->height
		|| x < 0 || x >= map->width
		|| map->grid[y][x] == '.');
}

static bool	is_map_walled(t_map *map)
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

bool	parse_map(t_map *map, char **lines)
{
	return (init_map(map, lines)
		&& valid_characters(map)
		&& is_map_walled(map));
}
