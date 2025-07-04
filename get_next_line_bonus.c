/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:52:45 by aosman            #+#    #+#             */
/*   Updated: 2025/06/28 16:54:00 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_check_newline(const char *str, int c)
{
	if (!str)
		return (NULL);
	if (c == 0)
		return ((char *)str);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

static char	*save_backup(char *backup)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	res = malloc(ft_strlen(backup) - i);
	if (!res)
		return (NULL);
	i++;
	j = 0;
	while (backup[i])
		res[j++] = backup[i++];
	res[j] = '\0';
	free(backup);
	return (res);
}

static char	*extract_line(char *backup)
{
	char	*line;
	size_t	i;
	size_t	len;

	if (!backup || backup[0] == '\0')
		return (NULL);
	len = 1;
	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
		len = 2;
	line = malloc(len + i);
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*backup_r(int fd, char *backup)
{
	ssize_t	bytes_r;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_r = 1;
	while (!ft_check_newline(backup, '\n') && bytes_r > 0)
	{
		bytes_r = read(fd, buffer, BUFFER_SIZE);
		if (bytes_r < 0)
		{
			free(backup);
			return (NULL);
		}
		buffer[bytes_r] = '\0';
		backup = ft_strjoin(backup, buffer);
		if (!backup)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	backup[fd] = backup_r(fd, backup[fd]);
	if (!backup[fd] || *backup[fd] == '\0')
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	line = extract_line(backup[fd]);
	backup[fd] = save_backup(backup[fd]);
	return (line);
}
