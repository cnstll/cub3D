/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:32:48 by calle             #+#    #+#             */
/*   Updated: 2020/11/25 10:10:32 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_src;
	size_t			i;

	ptr_src = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (ptr_src[i] == (unsigned char)c)
			return (ptr_src + i);
		i++;
	}
	return (NULL);
}
