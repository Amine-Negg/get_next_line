/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 19:12:00 by mohanegg          #+#    #+#             */
/*   Updated: 2026/11/23 15:55:41 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_from_fd(int fd, char **full_buffer)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp_buffer;
	ssize_t	bytes_read;

	while (!ft_strchr(*full_buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*full_buffer);
			*full_buffer = NULL;
			return (-1);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp_buffer = ft_strjoin(*full_buffer, buffer);
		if (!temp_buffer)
			return (-1);
		free(*full_buffer);
		*full_buffer = temp_buffer;
	}
	return (0);
}

char	*extract_line(char *full_buffer)
{
	size_t	line_len;

	line_len = 0;
	while (full_buffer[line_len] && full_buffer[line_len] != '\n')
		line_len++;
	if (full_buffer[line_len] == '\n')
		line_len++;
	return (ft_substr(full_buffer, 0, line_len));
}

int	update_buffer(char **full_buffer)
{
	size_t	leftover_len;
	size_t	remaining_index;
	char	*remaining;

	leftover_len = 0;
	while ((*full_buffer)[leftover_len]
		&& (*full_buffer)[leftover_len] != '\n')
		leftover_len++;
	if ((*full_buffer)[leftover_len] == '\n')
		leftover_len++;
	remaining = malloc(ft_strlen(*full_buffer) - leftover_len + 1);
	if (!remaining)
		return (-1);
	remaining_index = 0;
	while ((*full_buffer)[leftover_len])
	{
		remaining[remaining_index] = (*full_buffer)[leftover_len];
		remaining_index++;
		leftover_len++;
	}
	remaining[remaining_index] = '\0';
	free(*full_buffer);
	*full_buffer = remaining;
	return (1);
}

int	prepare_buffer(int fd, char **full_buffer)
{
	if (*full_buffer == NULL)
	{
		*full_buffer = malloc(1);
		if (!*full_buffer)
			return (-1);
		(*full_buffer)[0] = '\0';
	}
	if (read_from_fd(fd, full_buffer) == -1)
		return (-1);
	if ((*full_buffer)[0] == '\0')
	{
		free(*full_buffer);
		*full_buffer = NULL;
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*full_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (prepare_buffer(fd, &full_buffer) != 1)
		return (NULL);
	line = extract_line(full_buffer);
	if (!line)
		return (NULL);
	if (update_buffer(&full_buffer) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
