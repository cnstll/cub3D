/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:38:47 by calle             #+#    #+#             */
/*   Updated: 2020/12/01 18:16:33 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	malloc_subs(char **subs, char const *s, unsigned int st, size_t l)
{
	if (ft_strlen(s) <= st)
	{
		if (!(*subs = (char*)malloc(sizeof(char) * 1)))
			return (0);
	}
	else if (ft_strlen(s) > st && ft_strlen(s) - st < l)
	{
		if (!(*subs = (char*)malloc(sizeof(char) * (ft_strlen(s) - st + 1))))
			return (0);
	}
	else
	{
		if (!(*subs = (char*)malloc(sizeof(char) * (l + 1))))
			return (0);
	}
	return (1);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (NULL);
	if (malloc_subs(&subs, s, start, len) != 1)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		subs[i] = s[start];
		i++;
		start++;
	}
	subs[i] = '\0';
	return (subs);
}
