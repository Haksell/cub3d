#include "minitest.h"

static t_list	*ls(char *path)
{
	DIR				*dp;
	struct dirent	*ep;
	t_list			*lst;

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
	t_scene	scene;
	char	*filename;
	t_list	*filenames;
	bool	result;

	display_title(title);
	filenames = ls(directory);
	if (!expected)
		ft_lstadd_front(&filenames, ft_lstnew("scenes/invalid/notfound.rt"));
	while (filenames != NULL)
	{
		ft_bzero(&scene, sizeof(scene));
		filename = filenames->content;
		result = parse_scene(&scene, 2, (char *[]){"", filename, NULL});
		ft_assert(filename, result == expected);
		filenames = filenames->next;
	}
}

void	test_parse_scene(void)
{
	test("VALID SCENES", VALID_DIRECTORY, true);
	chmod("scenes/invalid/unreadable.rt", 0000);
	test("INVALID SCENES", INVALID_DIRECTORY, false);
	chmod("scenes/invalid/unreadable.rt", 0644);
}
