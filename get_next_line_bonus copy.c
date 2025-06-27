/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:52:45 by aosman            #+#    #+#             */
/*   Updated: 2025/06/25 17:26:07 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_get_line(char **buffer)
{
	char	*line;
	size_t	len;

	len = 0;
	if (!*buffer || !**buffer)
		return (NULL);
	while ((*buffer)[len] && (*buffer)[len] != '\n')
		len++;
	if ((*buffer)[len] == '\n')
		len++;
	line = (char *)malloc(len + 1);
	ft_copy_line(line, buffer, len);
	return (line);
}

static char	*ft_get_sbuff(char *str, char *buffer)
{
	char	*tmp;

	if (!str)
	{
		str = ft_strdup(buffer);
	}
	else
	{
		tmp = ft_strjoin(str, buffer);
		free(str);
		str = tmp;
	}
	return (str);
}
static void free_ptrs(char *buffer)
{
	free(buffer);
	buffer = NULL;
}
char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*saved_buff[1024];
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_check_newline(saved_buff[fd], '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free_ptrs(buffer);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		saved_buff[fd] = ft_get_sbuff(saved_buff[fd], buffer);
	}
	if (buffer)
		free(buffer);
	return (ft_get_line(&saved_buff[fd]));
}
