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
	bool	result;
	bool	is_unreadable;
	char	*filename;
	t_data	data;
	t_list	*filenames;

	display_title(title);
	filenames = ls(directory);
	if (!expected)
		ft_lstadd_front(&filenames, ft_lstnew("maps/invalid/notfound.cub"));
	while (filenames != NULL)
	{
		init_data(&data);
		filename = filenames->content;
		is_unreadable = ft_strcmp(filename, UNREADABLE_MAP) == 0;
		if (is_unreadable)
			chmod(UNREADABLE_MAP, 0000);
		result = parse_file(&data, 2, (char *[]){"", filename, NULL});
		if (is_unreadable)
			chmod(UNREADABLE_MAP, 0644);
		ft_assert(filename, result == expected);
		filenames = filenames->next;
	}
}

void	test_parse_file(void)
{
	test("VALID MAPS", VALID_DIRECTORY, true);
	test("INVALID MAPS", INVALID_DIRECTORY, false);
}
