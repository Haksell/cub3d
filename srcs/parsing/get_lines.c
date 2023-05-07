/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:09:15 by axbrisse          #+#    #+#             */
/*   Updated: 2023/05/07 09:09:15 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static ssize_t	count_file_size(char *filename)
{
	int		fd;
	char	buf[BUFFER_SIZE_3D];
	ssize_t	read_bytes;
	ssize_t	total;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (complain_int(ERROR_OPEN));
	total = 0;
	while (true)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE_3D);
		if (read_bytes == -1)
		{
			close(fd);
			return (complain_int(ERROR_READ));
		}
		total += read_bytes;
		if (read_bytes < BUFFER_SIZE_3D)
		{
			close(fd);
			return (total);
		}
	}
}

static char	*get_file_content(char *filename)
{
	int		fd;
	char	*res;
	ssize_t	bytes;
	ssize_t	total;

	total = count_file_size(filename);
	if (total == -1)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (complain_ptr(ERROR_OPEN));
	res = malloc((total + 1) * sizeof(char));
	if (res == NULL)
		return (close(fd), complain_ptr(ERROR_MALLOC));
	res[total] = '\0';
	bytes = read(fd, res, total);
	close(fd);
	if (bytes < total)
		return (free(res), complain_ptr(ERROR_READ));
	return (res);
}

static int	count_lines(char *file_content)
{
	int	num_lines;
	int	i;

	num_lines = 1;
	i = 0;
	while (file_content[i] != '\0')
	{
		num_lines += file_content[i] == '\n';
		++i;
	}
	return (num_lines);
}

static char	**split_lines(char *file_content)
{
	char	**lines;
	int		num_lines;
	int		arr_idx;
	int		i;

	file_content = ft_strtrim(file_content, "\n");
	if (file_content == NULL)
		return (complain_ptr(ERROR_MALLOC));
	num_lines = count_lines(file_content);
	lines = ft_calloc(num_lines + 1, sizeof(char *));
	if (lines == NULL)
		return (free(file_content), complain_ptr(ERROR_MALLOC));
	lines[0] = file_content;
	arr_idx = 1;
	i = 0;
	while (file_content[i] != '\0')
	{
		if (file_content[i] == '\n')
		{
			file_content[i] = '\0';
			lines[arr_idx++] = file_content + i + 1;
		}
		++i;
	}
	return (lines);
}

char	**get_lines(char *filename)
{
	char	*file_content;
	char	**lines;

	file_content = get_file_content(filename);
	if (file_content == NULL)
		return (NULL);
	lines = split_lines(file_content);
	free(file_content);
	return (lines);
}
