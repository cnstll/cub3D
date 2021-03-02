/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:07:48 by calle             #+#    #+#             */
/*   Updated: 2020/11/23 17:56:24 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	s1 = (char*)s1;
	s2 = (char*)s2;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && (s1[i] != '\0' && s2[i] != '\0') && (i < n - 1))
		i++;
	if ((s1[i] > s2[i]) || (s1[i] != '\0' && s2[i] == '\0'))
		return (1);
	else if ((s1[i] < s2[i]) || (s1[i] == '\0' && s2[i] != '\0'))
		return (-1);
	else
		return (0);
}
