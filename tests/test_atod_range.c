#include "minitest.h"

static void	check_bad(char *s, double min, double max)
{
	double	x;

	ft_assert(s, !ft_atod_range(s, &x, min, max));
}

static void	test_atod_range_bad(void)
{
	display_title("ATOD RANGE BAD");
	check_bad("4.2bonjour", -INFINITY, INFINITY);
	check_bad(".", -INFINITY, INFINITY);
	check_bad("-", -INFINITY, INFINITY);
	check_bad("-.", -INFINITY, INFINITY);
	check_bad("+", -INFINITY, INFINITY);
	check_bad("--42", -INFINITY, INFINITY);
	check_bad("127.0.0.1", -INFINITY, INFINITY);
	check_bad("69", 0, 42);
	check_bad("69", 111, 42);
	check_bad("69", 111, INFINITY);
	check_bad(N""N""N""N""N, -INFINITY, INFINITY);
}

static void	check_good(char *s, double target, double min,
	double max)
{
	double	x;

	ft_assert(s, ft_atod_range(s, &x, min, max) && is_close(x, target));
}

static void	test_atod_range_good(void)
{
	display_title("ATOD RANGE GOOD");
	check_good("42", 42.0, 0, 100);
	check_good("-42.0", -42.0, -100, 100);
	check_good("+42.0", 42.0, 0, 100);
	check_good("12.3456789", 12.3456789, 0, 100);
	check_good("-12.3456789", -12.3456789, -100, 100);
	check_good("1.", 1, 0, 100);
	check_good(".42", 0.42, 0, 1);
	check_good("69", 69, -INFINITY, 69);
	check_good("69", 69, 69, INFINITY);
	check_good("69", 69, 69, 69);
}

void	test_atod_range(void)
{
	test_atod_range_bad();
	test_atod_range_good();
}
