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

static void	set_dir_and_camera(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player.dir = (t_vec2){0, -1};
		data->camera = (t_vec2){-CAMERA_FOV, 0};
	}
	else if (c == 'E')
	{
		data->player.dir = (t_vec2){1, 0};
		data->camera = (t_vec2){0, -CAMERA_FOV};
	}
	else if (c == 'S')
	{
		data->player.dir = (t_vec2){0, 1};
		data->camera = (t_vec2){CAMERA_FOV, 0};
	}
	else
	{
		data->player.dir = (t_vec2){-1, 0};
		data->camera = (t_vec2){0, CAMERA_FOV};
	}
}

static bool	valid_character(t_data *data, int y, int x)
{
	const char	c = data->map.grid[y][x];

	if (ft_strchr(MAP_CHARACTERS, c) == NULL)
	{
		if (ft_strchr(PLAYER_CHARACTERS, c) == NULL)
			return (complain_bool(ERROR_INVALID_CHAR));
		else if (data->player.pos.x != -1)
			return (complain_bool(ERROR_MULTIPLAYER));
		else
		{
			data->player.pos = (t_vec2){x, y};
			set_dir_and_camera(data, c);
		}
	}
	return (true);
}

static bool	valid_characters(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (!valid_character(data, y, x))
				return (false);
			++x;
		}
		++y;
	}
	if (data->player.pos.x == -1)
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

bool	parse_map(t_data *data, char **lines)
{
	return (init_map(&data->map, lines)
		&& valid_characters(data)
		&& is_map_walled(&data->map));
}
