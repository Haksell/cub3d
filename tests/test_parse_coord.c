#include "minitest.h"

static void	check_bad(char *s)
{
	t_vec3	v;

	ft_assert(s, !parse_coord(ft_strdup(s), &v));
}

static void	test_parse_coord_bad(void)
{
	display_title("PARSE COORD BAD");
	check_bad(",,");
	check_bad("42.35,42");
	check_bad("42,42.,");
	check_bad("42,42,42,");
	check_bad("42,42.00,42,42");
	check_bad("42,42,42,42");
	check_bad("0.0,0.0,"N""N""N""N""N""N""N"");
}

static void	check_good(char *s, double x, double y, double z)
{
	t_vec3	v;

	ft_assert(s, parse_coord(ft_strdup(s), &v)
		&& is_close(x, v.x) && is_close(y, v.y) && is_close(z, v.z));
}

static void	test_parse_coord_good(void)
{
	display_title("PARSE COORD GOOD");
	check_good("50.0,0.0,20.6", 50, 0, 20.6);
	check_good("42,42.,42.0", 42, 42, 42);
	check_good("+42,-42,0", 42, -42, 0);
	check_good("-0,42,42", 0, 42, 42);
	check_good("-1.23,0.0,1.23", -1.23, 0, 1.23);
}

void	test_parse_coord(void)
{
	test_parse_coord_bad();
	test_parse_coord_good();
}
