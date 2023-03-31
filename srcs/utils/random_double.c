#include "minirt.h"

static unsigned int	get_random_uint(void)
{
	static unsigned int	x = 3941839098;

	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return (x);
}

double	get_random_double(void)
{
	static unsigned long	max_plus_one = 1l << 32l;

	return ((double)get_random_uint() / (double)max_plus_one);
}

double	get_random_double_range(double min, double max)
{
	return (min + (max - min) * get_random_double());
}
