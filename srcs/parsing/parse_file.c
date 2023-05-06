#include "cub3d.h"

static bool	is_all_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '\0')
			return (false);
		++i;
	}
	return (true);
}

bool	parse_file(t_data *data, int argc, char **argv)
{
	char	**lines;
	char	**lines_to_free;

	if (argc != 2 || !ft_endswith(argv[1], ".cub"))
		return (complain_bool(USAGE));
	lines = get_lines(argv[1]);
	if (lines == NULL)
		return (false);
	lines_to_free = lines;
	if (!parse_infos(&data->infos, &lines))
		return (free_lines(lines_to_free), false);
	while (*lines != NULL && is_all_space(*lines))
		++lines;
	if (!parse_map(data, lines))
		return (free_lines(lines_to_free), false);
	return (free_lines(lines_to_free), true);
}
