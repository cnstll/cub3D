/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:39:27 by calle             #+#    #+#             */
/*   Updated: 2021/01/14 18:00:46 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			integer_size(long int n)
{
	int						size;
	long unsigned int		nb;

	size = 0;
	if (n < 0)
	{
		size++;
		nb = -n;
	}
	else
		nb = n;
	while (nb != 0)
	{
		nb = nb / 10;
		size++;
	}
	if (n == 0)
		size++;
	return (size);
}

char				*ft_itoa(long int n)
{
	int						len;
	char					*str;
	int						i;
	long unsigned int		nb;

	len = integer_size(n);
	i = len - 1;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = 0;
	if (n < 0)
		nb = -n;
	else
		nb = n;
	while (i > 0)
	{
		str[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	if (n < 0)
		str[i] = '-';
	else
		str[i] = (nb % 10) + 48;
	return (str);
}
/*
#include <limits.h>
#include <stdio.h>
int main()
{
	printf("%s\n", ft_itoa(INT_MIN));
	printf("%s\n", ft_itoa(-4));
	return (1);
}*/
