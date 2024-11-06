/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:44:58 by jhogonca          #+#    #+#             */
/*   Updated: 2024/11/06 23:38:55 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*append_line(char *current_line, char *buffer, int buffer_size,
	int *total_length)
{
	char	*new_line;

	auto int new_index = 0;
	auto int current_index = 0;
	auto int buffer_index = 0;
	new_line = current_line;
	*total_length += buffer_size;
	current_line = malloc((*total_length + 1) * sizeof(char));
	if (current_line)
	{
		current_line[*total_length] = 0;
		while (new_line && new_line[current_index])
			current_line[new_index++] = new_line[current_index++];
		current_index = 0;
		while (buffer && buffer[current_index])
		{
			if (current_index < buffer_size)
				current_line[new_index++] = buffer[current_index];
			else
				buffer[buffer_index++] = buffer[current_index];
			buffer[current_index++] = 0;
		}
	}
	free(new_line);
	return (current_line);
}

void	readline(int fd, char buffer[], int *buffer_size, char **line)
{
	if (buffer[0] == 0)
		*buffer_size = read(fd, buffer, BUFFER_SIZE);
	if (*buffer_size == -1)
	{
		free(*line);
		*line = NULL;
	}
}

char	*read_buffer(int fd, char buffers[][BUFFER_SIZE + 1], int *buffer_size)
{
	char	*line;
	int		read_status;
	int		total_length;

	line = NULL;
	read_status = 1;
	total_length = 0;
	while (read_status > 0)
	{
		readline(fd, buffers[fd], buffer_size, &line);
		read_status = *buffer_size;
		if (*buffer_size > 0)
		{
			*buffer_size = 0;
			while (buffers[fd][*buffer_size] \
				&& buffers[fd][*buffer_size] != '\n')
				++*buffer_size;
			read_status = (read_status == *buffer_size);
			*buffer_size += (buffers[fd][*buffer_size] == '\n');
			line = append_line(line, buffers[fd], *buffer_size, &total_length);
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	int			buffer_length;
	static char	buffers[FOPEN_MAX][BUFFER_SIZE + 1];

	buffer_length = 0;
	if ((fd < 0 || fd > FOPEN_MAX) || BUFFER_SIZE <= 0)
		return (NULL);
	while (buffers[fd][buffer_length])
		buffer_length++;
	return (read_buffer(fd, buffers, &buffer_length));
}
