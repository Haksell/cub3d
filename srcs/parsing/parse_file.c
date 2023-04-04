#include "cub3d.h"

bool	parse_file(t_data *data, int argc, char **argv)
{
	char	**lines;

	if (argc != 2 || !ft_endswith(argv[1], ".cub"))
		return (complain_bool(USAGE_MANDATORY));
	lines = get_lines(argv[1]);
	if (lines == NULL)
		return (complain_bool(MALLOC_ERROR));
	if (!parse_infos(&data->infos, &lines))
		return (complain_bool(ERROR_PARSE_INFOS));
	if (!parse_map(&data->map, lines))
		return (complain_bool(ERROR_PARSE_MAP));
	return (true);
}
