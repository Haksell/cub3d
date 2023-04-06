#include "test3d.h"

static int	definitely_not_a_global(bool update)
{
	static int	status = EXIT_SUCCESS;

	if (update)
		status = EXIT_FAILURE;
	return (status);
}

void	display_title(char *s)
{
	ft_printf("%s--- %s ---\n%s", BOLDBLUE, s, RESET);
}

void	ft_assert(char *test_name, bool result)
{
	char	*color;
	char	*verdict;

	if (result)
	{
		color = GREEN;
		verdict = "OK";
	}
	else
	{
		color = RED;
		verdict = "KO";
		definitely_not_a_global(true);
	}
	ft_printf("%s%s: %s\n%s", color, test_name, verdict, RESET);
}

int	main(void)
{
	test_parse_file();
	return (definitely_not_a_global(false));
}
