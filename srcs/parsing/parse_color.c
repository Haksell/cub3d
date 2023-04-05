#include "cub3d.h"

static bool	get_commas(char *s, char **s2, char **s3)
{
	*s2 = ft_strchr(s, ',');
	if (*s2 == NULL)
		return (false);
	**s2 = '\0';
	++(*s2);
	*s3 = ft_strchr(*s2, ',');
	if (*s3 == NULL)
		return (false);
	**s3 = '\0';
	++(*s3);
	return (true);
}

static bool	parse_component(char *s, int *x)
{
	int	n;
	int	i;

	if (s[0] == '\0')
		return (false);
	n = 0;
	i = 0;
	while (ft_isdigit(s[i]))
	{
		n = 10 * n + s[i] - '0';
		if (n > 255)
			return (false);
		++i;
	}
	*x = n;
	return (s[i] == '\0');
}

bool	parse_color(char *s, int *color)
{
	int		r;
	int		g;
	int		b;
	char	*s2;
	char	*s3;

	if (*color != -1)
		return (complain_bool(ERROR_DUPLICATE_COLOR));
	if (!get_commas(s, &s2, &s3)
		|| !parse_component(s, &r)
		|| !parse_component(s2, &g)
		|| !parse_component(s3, &b))
		return (complain_bool(ERROR_PARSING_COLOR));
	*color = r << 16 | g << 8 | b;
	return (true);
}
