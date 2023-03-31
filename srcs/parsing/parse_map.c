#include "cub3d.h"

bool	parse_map(t_map *map, int argc, char **argv)
{
	int	fd;

	if (argc != 2 || !ft_endswith(argv[1], ".cub"))
		return (complain_bool(USAGE_MANDATORY));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (complain_bool(OPEN_ERROR));
	close(fd);
	(void)map;
	return (true);
}
