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

	if (argc != 2 || !ft_endswith(argv[1], ".cub"))
		return (complain_bool(USAGE_MANDATORY));
	lines = get_lines(argv[1]);
	if (lines == NULL)
		return (false);
	if (!parse_infos(&data->infos, &lines))
		return (false);
	while (*lines != NULL && is_all_space(*lines))
		++lines;
	if (!parse_map(data, lines))
		return (false);
	return (true);
}
