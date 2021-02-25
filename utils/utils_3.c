/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:37:53 by calle             #+#    #+#             */
/*   Updated: 2021/02/24 15:46:40 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

size_t				ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char			*ft_strdup(const char *s)
{
	char			*dup;
	unsigned int	i;

	i = 0;
	if (!(dup = malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (i <= ft_strlen(s))
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

char			*ft_str_append(char *s, char c)
{
	unsigned int	len;
	char			*r;
	int				i;

	len = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	if (!(r = (char *)malloc(sizeof(char) * (len + 2))))
		return (0);
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i++] = c;
	r[i] = '\0';
	if ((*s))
		free(s);
	return (r);
}

int				*ft_lite_atoi(const char *s)	
{
	char	*nbr;
	int		n;
	int		i;

	nbr = (char *)s;
	i = 0;
	n = 0;
	while (nbr[i] > 47 && nbr[i] < 58)
	{
		if (nbr[i + 1] > 47 && nbr[i + 1] < 58)
			n = (n + (int)(nbr[i]) % 48) * 10;
		else
			n = (n + (int)(nbr[i]) % 48);
		i++;
	}
	return (n);
}
