/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:52:27 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/13 17:11:31 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	uc = (unsigned char)c;
	size_t				i;
	char				*ptr;

	i = 0;
	ptr = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == uc)
			ptr = (char *)(s + i);
		i++;
	}
	if (uc == 0)
		ptr = (char *)(s + i);
	return (ptr);
}
