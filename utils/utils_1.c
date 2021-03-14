/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calle <calle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:24:38 by calle             #+#    #+#             */
/*   Updated: 2021/03/14 16:53:12 by calle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*d;
	int		l1;
	int		l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	d = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (d == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && i < l1 && s1[i])
		d[j++] = s1[i++];
	i = 0;
	while (s2 && i < l2 && s2[i])
		d[l1++] = s2[i++];
	d[l1] = '\0';
	if (s1)
		free(s1);
	return (d);
}

int		c_in_s(char c, char *s)
{
	int		i;

	i = 0;
	if (!c)
		return (0);
	while (s && s[i])
		if (s[i++] == c)
			return (1);
	return (0);
}

char	*ft_strdup_till_char(char *s, char c, int start)
{
	int		i;
	int		size;
	char	*dup;

	i = start;
	if (!s)
		return (NULL);
	while (s[i] != c && s[i])
		i++;
	size = i - start;
	dup = (char *)(malloc(sizeof(char) * (size + 1)));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[start] && i < size)
		dup[i++] = s[start++];
	dup[i] = '\0';
	return (dup);
}
