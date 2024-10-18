/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:08:18 by alvera-f          #+#    #+#             */
/*   Updated: 2024/10/15 12:08:21 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	char	*src;

	src = (char *)s;
	copy = malloc(ft_strlen(src) + 1);
	if (!copy)
		return (NULL);
	if (copy != NULL)
		return (ft_strcpy(copy, src));
	return (copy);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	while (*str != '\0')
	{
		if (*str == ch)
			return ((char *)str);
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*copy;

	if (!s1 || !s2)
		return (0);
	copy = malloc ((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!copy)
		return (0);
	ft_strlcpy(copy, s1, ft_strlen(s1) + 1);
	ft_strlcpy(copy + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (copy);
}


