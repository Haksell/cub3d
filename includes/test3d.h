/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:09:54 by axbrisse          #+#    #+#             */
/*   Updated: 2023/05/07 09:09:55 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST3D_H
# define TEST3D_H

# include "cub3d.h"

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

# define RESET "\033[0m"
# define BOLDBLUE "\033[1m\033[34m"
# define RED "\033[31m"
# define GREEN "\033[32m"

# define VALID_DIRECTORY "maps/valid/"
# define INVALID_DIRECTORY "maps/invalid/"
# define MAP_NOT_FOUND "maps/invalid/notfound.cub"
# define MAP_UNREADABLE "maps/invalid/unreadable.cub"

void	display_title(char *s);
void	ft_assert(char *test_name, bool result);
void	test_parse_file(void);

#endif
