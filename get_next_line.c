/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:25:22 by aosman            #+#    #+#             */
/*   Updated: 2025/06/28 16:52:25 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = backup_r(fd, backup);
	if (!backup || *backup == '\0')
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	line = extract_line(backup);
	backup = save_backup(backup);
	return (line);
}
