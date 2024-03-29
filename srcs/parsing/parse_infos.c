/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:09:24 by axbrisse          #+#    #+#             */
/*   Updated: 2023/05/07 09:09:25 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	set_texture(char *s, char **texture)
{
	if (*texture != NULL)
		return (complain_bool(ERROR_DUPLICATE_TEXTURE));
	*texture = ft_strdup(s);
	return (*texture != NULL);
}

static bool	parse_info(t_infos *infos, char **line)
{
	if (line[0] == NULL)
		return (true);
	if (arrlen(line) != 2)
		return (complain_bool(ERROR_PARSING_LINE));
	else if (ft_strcmp(line[0], ID_NORTH) == 0)
		return (set_texture(line[1], &infos->path_north_texture));
	else if (ft_strcmp(line[0], ID_EAST) == 0)
		return (set_texture(line[1], &infos->path_east_texture));
	else if (ft_strcmp(line[0], ID_SOUTH) == 0)
		return (set_texture(line[1], &infos->path_south_texture));
	else if (ft_strcmp(line[0], ID_WEST) == 0)
		return (set_texture(line[1], &infos->path_west_texture));
	else if (ft_strcmp(line[0], ID_FLOOR) == 0)
		return (parse_color(line[1], &infos->floor));
	else if (ft_strcmp(line[0], ID_CEIL) == 0)
		return (parse_color(line[1], &infos->ceil));
	else
		return (complain_bool(ERROR_INVALID_IDENTIFIER));
}

static bool	complete_infos(t_infos *infos)
{
	return (infos->path_north_texture != NULL
		&& infos->path_east_texture != NULL
		&& infos->path_south_texture != NULL
		&& infos->path_west_texture != NULL
		&& infos->floor != -1
		&& infos->ceil != -1);
}

bool	parse_infos(t_infos *infos, char ***lines)
{
	char	**line;

	while (true)
	{
		line = ft_split(**lines, ' ');
		if (line == NULL)
			return (complain_bool(ERROR_MALLOC));
		if (!parse_info(infos, line))
			return (ft_free_double((void ***)&line), false);
		++(*lines);
		ft_free_double((void ***)&line);
		if (complete_infos(infos))
			return (true);
		if (**lines == NULL)
			return (complain_bool(ERROR_INCOMPLETE_INFORMATIONS));
	}
}
