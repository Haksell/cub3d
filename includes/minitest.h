#ifndef MINITEST_H
# define MINITEST_H

# include "minirt.h"

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

# define RESET "\033[0m"
# define BOLDBLUE "\033[1m\033[34m"
# define RED "\033[31m"
# define GREEN "\033[32m"

# define VALID_DIRECTORY "scenes/valid/"
# define INVALID_DIRECTORY "scenes/invalid/"

# define N "9999999999999999999999999999999999999999999999999999999999999999999"

void	display_title(char *s);
void	ft_assert(char *test_name, bool result);
void	test_atod_range(void);
void	test_parse_color(void);
void	test_parse_coord(void);
void	test_parse_scene(void);

#endif
