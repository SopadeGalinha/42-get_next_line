/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:50:30 by jhogonca          #+#    #+#             */
/*   Updated: 2023/04/23 21:50:30 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*process_line(char *new_line, char *buffer, int buffer_size, int *line_length)
{
	char	*line;
	int		index;
	int		size_line;
	int		buffer_index;

	index = 0;
	size_line = 0;
	buffer_index = 0;
	line = new_line;
	*line_length += buffer_size;
	new_line = malloc(*line_length + 1 * sizeof(char));
	if (new_line)
	{
		new_line[*line_length] = 0;
		while (line && line[size_line])
			new_line[index++] = line[size_line++];
		size_line = 0;
		while (buffer && buffer[size_line])
		{
			if (size_line < buffer_size)
				new_line[index++] = buffer[size_line];
			else
				buffer[buffer_index++] = buffer[size_line];
			buffer[size_line++] = 0;
		}
	}
	free(line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	int			flag;
	char		*line;
	int			size_line;
	int			size_buffer;
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];

	flag = 1;
	size_buffer = 0;
	line = NULL;
	size_line = 0;
	if ((fd < 0 || fd > FOPEN_MAX) || !BUFFER_SIZE)
		return (NULL);
	while (buffer[fd][size_buffer])
		size_buffer++;
	while (flag > 0)
	{
		if (!buffer[fd][0])
			size_buffer = read(fd, buffer[fd], BUFFER_SIZE);
		flag = size_buffer;
		if (size_buffer > 0)
		{
			size_buffer = 0;
			while (buffer[fd][size_buffer] && buffer[fd][size_buffer] != '\n')
				size_buffer++;
			flag = (flag == size_buffer);
			size_buffer += buffer[fd][size_buffer] == '\n';
			line = process_line(line, buffer[fd], size_buffer, &size_line);
		}
	}
	return (line);
}

int main(int argc, char const *argv[])
{
	int		fd;
	char	*line;

	fd = open(".lovezin.txt", O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
