/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:26:12 by aosman            #+#    #+#             */
/*   Updated: 2025/06/22 16:15:44 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = ft_strlen(str);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_check_newline(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (c == 0)
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*res;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc(s1_len + s2_len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		res[i + s1_len] = s2[i];
		i++;
	}
	res[i + s1_len] = '\0';
	return (res);
}

void	ft_copy_line(char *dest, char **buffer, size_t len)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		dest[i] = (*buffer)[i];
		i++;
	}
	dest[i] = '\0';
	if ((*buffer)[len])
	{
		tmp = ft_strdup(*buffer + len);
	}
	else
		tmp = NULL;
	free(*buffer);
	*buffer = tmp;
}
