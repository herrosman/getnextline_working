/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:26:12 by aosman            #+#    #+#             */
/*   Updated: 2025/06/27 20:00:33 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d_ptr;
	const char	*s_ptr;

	if (!dest && !src)
		return (NULL);
	d_ptr = (char *)dest;
	s_ptr = (const char *)src;
	i = 0;
	while (i < n)
	{
		d_ptr[i] = s_ptr[i];
		i++;
	}
	return (dest);
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	if (s1)
		ft_memcpy(res, s1, len1);
	if (s2)
		ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	free(s1);
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
