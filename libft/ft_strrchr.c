/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:26:07 by calle             #+#    #+#             */
/*   Updated: 2020/12/01 18:44:30 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*ptr_chr;
	int		i;

	c = (unsigned char)c;
	s = (char*)s;
	ptr_chr = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			ptr_chr = (char*)s + i;
		i++;
	}
	if (c == '\0')
		ptr_chr = (char*)s + i;
	return (ptr_chr);
}
