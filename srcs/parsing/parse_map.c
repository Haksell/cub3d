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

bool	parse_map(t_data *data, char **lines)
{
	return (init_map(&data->map, lines)
		&& valid_characters(data)
		&& is_map_walled(&data->map));
}
