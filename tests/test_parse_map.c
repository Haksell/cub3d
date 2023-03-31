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
	t_map	map;
	char	*filename;
	t_list	*filenames;
	bool	result;

	display_title(title);
	filenames = ls(directory);
	if (!expected)
		ft_lstadd_front(&filenames, ft_lstnew("maps/invalid/notfound.cub"));
	while (filenames != NULL)
	{
		ft_bzero(&map, sizeof(map));
		filename = filenames->content;
		result = parse_map(&map, 2, (char *[]){"", filename, NULL});
		ft_assert(filename, result == expected);
		filenames = filenames->next;
	}
}

void	test_parse_map(void)
{
	test("VALID MAPS", VALID_DIRECTORY, true);
	chmod("maps/invalid/unreadable.cub", 0000);
	test("INVALID MAPS", INVALID_DIRECTORY, false);
	chmod("maps/invalid/unreadable.cub", 0644);
}
