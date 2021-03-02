/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:12:56 by calle             #+#    #+#             */
/*   Updated: 2020/12/01 14:47:18 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	c = (unsigned char)c;
	while (s[i] || s[i] == c)
	{
		if (s[i] == c)
			return ((char*)s + i);
		i++;
	}
	return (0);
}
