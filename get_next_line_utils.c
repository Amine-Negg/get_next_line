/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 18:08:53 by mohanegg          #+#    #+#             */
/*   Updated: 2026/11/22 01:45:36 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (s[i] == '\0')
	{
		if (c == 0)
		{
			return ((char *)(s + i));
		}
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jo;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	jo = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!jo)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		jo[j++] = s1[i++];
	i = 0;
	while (s2[i])
		jo[j++] = s2[i++];
	jo[j] = '\0';
	return (jo);
}

size_t	ft_strlen(const char *sting)
{
	size_t	index;

	index = 0;
	while (sting[index])
	{
		index++;
	}
	return (index);
}