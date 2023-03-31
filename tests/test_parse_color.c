#include "minitest.h"

static void	check_bad(char *s)
{
	t_vec3	v;

	ft_assert(s, !parse_color(ft_strdup(s), &v));
}

static void	test_parse_color_bad(void)
{
	display_title("PARSE COLOR BAD");
	check_bad(",,");
	check_bad("42,42");
	check_bad("42,42,");
	check_bad("42,42,42,");
	check_bad("42,42,42,42");
	check_bad("42,-42,42");
	check_bad("-0,42,42");
	check_bad("42,+42,42");
	check_bad("42,42.0,42");
	check_bad("0,256,0");
}

static void	check_good(char *s, double x, double y, double z)
{
	t_vec3	v;

	ft_assert(s,
		parse_color(ft_strdup(s), &v) && x == v.x && y == v.y && z == v.z);
}

static void	test_parse_color_good(void)
{
	display_title("PARSE COLOR GOOD");
	check_good("0,0,0", 0, 0, 0);
	check_good("42,42,42", 42, 42, 42);
	check_good("0,90,156", 0, 90, 156);
	check_good("255,255,255", 255, 255, 255);
}

void	test_parse_color(void)
{
	test_parse_color_bad();
	test_parse_color_good();
}
