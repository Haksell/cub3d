#include "cub3d.h"

int	clamp(int n, int min, int max)
{
	if (n < min)
		return (min);
	else if (n > max)
		return (max);
	else
		return (n);
}

int	arrlen(char **lines)
{
	int	n;

	n = 0;
	while (lines[n] != NULL)
		++n;
	return (n);
}
