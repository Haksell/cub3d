#include "minirt.h"

bool	ft_atod(char *s, double *ans)
{
	int		i;
	double	sign;
	double	decimal;

	i = (s[0] == '-' || s[0] == '+');
	if (s[i] == '\0' || (s[i] == '.' && s[i + 1] == '\0'))
		return (false);
	sign = (s[0] != '-') - (s[0] == '-');
	*ans = 0;
	while (ft_isdigit(s[i]))
		*ans = 10 * *ans + s[i++] - '0';
	if (s[i] == '.')
	{
		++i;
		decimal = 0.1;
		while (ft_isdigit(s[i]))
		{
			*ans += decimal * (s[i++] - '0');
			decimal *= 0.1;
		}
	}
	*ans *= sign;
	return (s[i] == '\0' && isfinite(*ans));
}

bool	ft_atod_range(char *s, double *ans, double min, double max)
{
	return (ft_atod(s, ans) && *ans >= min && *ans <= max);
}
