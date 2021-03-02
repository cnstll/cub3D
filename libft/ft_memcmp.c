/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:41:47 by calle             #+#    #+#             */
/*   Updated: 2020/11/21 18:54:41 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*p_s1;
	unsigned char	*p_s2;

	i = 0;
	p_s1 = (unsigned char*)s1;
	p_s2 = (unsigned char*)s2;
	if (n == 0)
		return (0);
	while (p_s1[i] == p_s2[i] && i < n - 1)
		i++;
	if (p_s1[i] == p_s2[i])
		return (0);
	else
		return (p_s1[i] - p_s2[i]);
}
