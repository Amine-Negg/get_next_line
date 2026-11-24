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

char	*get_next_line(int fd)
{
	static char	*full_buffer;
	char		*temp_buffer;
	char		buffer[BUFFER_SIZE + 1];
	char		*newline;
	char		*line;
	char		*remaining;
	size_t		index;
	size_t		line_len;
	size_t		leftover_len;
	size_t		remaining_index;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
    	return (NULL);
	if (full_buffer == NULL)
	{
		full_buffer = malloc(1);
    	if (!full_buffer)
        	return (NULL);
    	full_buffer[0] = '\0';
	}
	while (!ft_strchr(full_buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(full_buffer);
			full_buffer = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		temp_buffer = ft_strjoin(full_buffer , buffer);
		if (!temp_buffer)
			return (NULL);
		free(full_buffer);
		full_buffer = temp_buffer;
	}
	if (full_buffer[0] == '\0')
	{
		free(full_buffer);
		full_buffer = NULL;
		return (NULL);
	}
	newline = ft_strchr(full_buffer, '\n');
	if (newline)
		line_len = newline - full_buffer + 1;
	else
		line_len = ft_strlen(full_buffer);
	line = malloc(line_len + 1);
	if (!line)
		return (NULL);
	index = 0;
	while (full_buffer[index] && index < line_len)
	{
		line[index] = full_buffer[index];
		index++;
	}
	line[index] = '\0';
	leftover_len = 0;
	while (full_buffer[index])
	{
		index++;
		leftover_len++;
	}
	remaining = malloc(leftover_len + 1);
	if (!remaining)
	{
		free(line);
		return (NULL);
	}
	
	index = index - leftover_len;
	remaining_index = 0;
	while (full_buffer[index])
	{
		remaining[remaining_index] = full_buffer[index];
		remaining_index++;
		index++;
	}
	remaining[remaining_index] = '\0';
	free(full_buffer);
	full_buffer = remaining;
	return(line);
}
