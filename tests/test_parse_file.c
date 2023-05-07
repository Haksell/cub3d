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
	char	*filename;
	t_data	data;
	t_list	*filenames;
	t_list	*curr;

	display_title(title);
	filenames = ls(directory);
	// if (!expected)
	// 	ft_lstadd_front(&filenames, ft_lstnew(ft_strdup(MAP_NOT_FOUND)));
	curr = filenames;
	while (curr != NULL)
	{
		init_data(&data);
		filename = curr->content;
		// if (ft_strcmp(filename, MAP_UNREADABLE) == 0)
		// 	chmod(MAP_UNREADABLE, 0000);
		result = parse_file(&data, 2, (char *[]){"", filename, NULL});
		ft_assert(filename, result == expected);
		// if (ft_strcmp(filename, MAP_UNREADABLE) == 0)
		// 	chmod(MAP_UNREADABLE, 0644);
		curr = curr->next;
		free_data(&data);
	}
	ft_lstclear(&filenames, (void (*)(void *))ft_free);
}

void	test_parse_file(void)
{
	test("VALID MAPS", VALID_DIRECTORY, true);
	test("INVALID MAPS", INVALID_DIRECTORY, false);
}
