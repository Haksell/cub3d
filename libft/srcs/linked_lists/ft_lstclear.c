/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:35:04 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/01 06:48:45 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive_clear(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	recursive_clear(lst->next, del);
	if (del != NULL)
		del(&lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	recursive_clear(*lst, del);
	*lst = NULL;
}
