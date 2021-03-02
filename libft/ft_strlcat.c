/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:39:58 by calle             #+#    #+#             */
/*   Updated: 2020/11/23 16:26:06 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	len;

	i = 0;
	dst_len = ft_strlen((const char*)dst);
	src_len = ft_strlen(src);
	len = i + dst_len;
	if (dst_len >= size)
		return (size + src_len);
	while (size != 0 && i < size - dst_len - 1 && src[i])
	{
		dst[len] = src[i];
		i++;
		len++;
	}
	dst[len] = '\0';
	return (dst_len + src_len);
}
