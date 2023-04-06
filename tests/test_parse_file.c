#include "test3d.h"

static t_list	*ls(char *path)
{
	DIR				*dp;
	t_list			*lst;
	struct dirent	*ep;

	lst = NULL;
	dp = opendir(path);
	ep = readdir(dp);
	while (ep != NULL)
	{
		if (ep->d_name[0] != '.')
			ft_lstadd_front(&lst, ft_lstnew(ft_strjoin(path, ep->d_name)));
		ep = readdir(dp);
	}
	closedir(dp);
	ft_lst_sort(lst, (int (*)(void *, void *))ft_strcmp);
	return (lst);
}

static void	test(char *title, char *directory, bool expected)
{
	bool	is_unreadable;
	char	*filename;
	t_data	data;
	t_list	*to_free;
	t_list	*filenames;

	display_title(title);
	filenames = ls(directory);
	if (!expected)
		ft_lstadd_front(&filenames, ft_lstnew(ft_strdup(MAP_NOT_FOUND)));
	to_free = filenames;
	while (filenames != NULL)
	{
		init_data(&data);
		filename = filenames->content;
		is_unreadable = ft_strcmp(filename, MAP_UNREADABLE) == 0;
		if (is_unreadable)
			chmod(MAP_UNREADABLE, 0000);
		ft_assert(filename, parse_file(&data, 2, (char *[]){"", filename, NULL}) == expected);
		if (is_unreadable)
			chmod(MAP_UNREADABLE, 0644);
		filenames = filenames->next;
	}
	ft_lstclear(&to_free, (void (*)(void *))ft_free);
	free_data(&data);
}

void	test_parse_file(void)
{
	test("VALID MAPS", VALID_DIRECTORY, true);
	test("INVALID MAPS", INVALID_DIRECTORY, false);
}
