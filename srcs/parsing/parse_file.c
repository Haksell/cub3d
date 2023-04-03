#include "cub3d.h"

static bool	set_texture(char *s, char **texture)
{
	if (*texture != NULL)
		return (false);
	*texture = ft_strdup(s);
	return (*texture != NULL);
}

static bool	parse_info(t_infos *infos, char **line)
{
	if (line[0] == NULL)
		return (true);
	if (arrlen(line) != 2)
		return (false);
	else if (ft_strcmp(line[0], ID_NORTH) == 0)
		return (set_texture(line[1], &infos->path_north_texture));
	else if (ft_strcmp(line[0], ID_EAST) == 0)
		return (set_texture(line[1], &infos->path_east_texture));
	else if (ft_strcmp(line[0], ID_SOUTH) == 0)
		return (set_texture(line[1], &infos->path_south_texture));
	else if (ft_strcmp(line[0], ID_WEST) == 0)
		return (set_texture(line[1], &infos->path_west_texture));
	else if (ft_strcmp(line[0], ID_FLOOR) == 0)
		return (parse_color(line[1], &infos->floor));
	else if (ft_strcmp(line[0], ID_CEIL) == 0)
		return (parse_color(line[1], &infos->ceil));
	else
		return (false);
}

static bool	complete_informations(t_infos *infos)
{
	return (infos->path_north_texture != NULL
		&& infos->path_east_texture != NULL
		&& infos->path_south_texture != NULL
		&& infos->path_west_texture != NULL
		&& infos->floor != -1
		&& infos->ceil != -1);
}

static bool	parse_informations(t_infos *infos, char ***lines)
{
	char	**line;
	int		i;

	i = 0;
	while ((*lines)[i] != NULL)
	{
		line = ft_split((*lines)[i], ' ');
		if (line == NULL || !parse_info(infos, line))
			return (false);
		if (complete_informations(infos))
			return (true);
		ft_free_double((void ***)&line);
		++(*lines);
	}
	return (complete_informations(infos));
}

bool	parse_file(t_data *data, int argc, char **argv)
{
	char	**lines;

	if (argc != 2 || !ft_endswith(argv[1], ".cub"))
		return (complain_bool(USAGE_MANDATORY));
	lines = get_lines(argv[1]);
	if (lines == NULL)
		return (complain_bool(MALLOC_ERROR));
	if (!parse_informations(&data->infos, &lines))
		return (complain_bool("Map is invalid."));
	return (true);
}
