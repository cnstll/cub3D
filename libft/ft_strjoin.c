/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:20:35 by calle             #+#    #+#             */
/*   Updated: 2021/01/15 12:12:04 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*r;
	size_t	i;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	i = 0;
	if (!(r = (char *)malloc(sizeof(char) * (l1 + l2 + 1))) || !s1 || !s2)
		return (NULL);
	while (i < l1)
	{
		r[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		r[l1] = s2[i];
		i++;
		l1++;
	}
	r[l1] = '\0';
	return (r);
}
