/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:34:13 by calle             #+#    #+#             */
/*   Updated: 2020/12/01 18:15:39 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*ptr_dest;
	const char	*ptr_src;
	char		*ptr_enddest;
	const char	*ptr_endsrc;

	ptr_dest = dest;
	ptr_src = src;
	if (!dest || !src)
		return (dest);
	ptr_enddest = dest + (n - 1);
	ptr_endsrc = src + (n - 1);
	if (ptr_dest < ptr_src)
		while (n--)
			*ptr_dest++ = *ptr_src++;
	else
		while (n--)
			*ptr_enddest-- = *ptr_endsrc--;
	return (dest);
}
