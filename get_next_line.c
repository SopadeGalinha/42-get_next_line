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

	// Update the total size of the line to allocate memory for the new 'line'
	*line_length += buffer_size;
	new_line = malloc(*line_length + 1 * sizeof(char));
	if (new_line)
	{
		new_line[*line_length] = 0;  // Add the null terminator at the end of the new 'line'

		// Copy characters from 'line' to the new 'line'
		while (line && line[size_line])
			new_line[index++] = line[size_line++];
		
		size_line = 0;  // Reset size_line to be used again
		
		// Copy characters from 'buffer' to the new 'line'
		while (buffer && buffer[size_line])
		{
			/* Copy characters from 'buffer' to the new 'line' until the newline character is found and
			 * store the remaining characters at the beginning of the buffer */
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
	// Create a static buffer to store the read lines from the file descriptor with the size of BUFFER_SIZE + 1
	int			flag;
	int			size_buffer;
	int			size_line;
	char		*line;
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];

	flag = 1;			// Initialize to 1 to enter the loop
	size_buffer = 0;
	line = NULL;
	size_line = 0;
	if ((fd < 0 || fd > FOPEN_MAX) || !BUFFER_SIZE) // return null if the fd or buffersize is invalid
		return (NULL);

	// Loop to find the position of the newline character
	while (buffer[fd][size_buffer])
		size_buffer++;
	/*	Loop to read and process lines from the file descriptor
		- The condition to enter the loop is the flag variable */
	while (flag > 0)
	{
		// if the buffer is empty it will read from the file descriptor
		if (!buffer[fd][0])
			size_buffer = read(fd, buffer[fd], BUFFER_SIZE);

		flag = size_buffer;  // Update flag with the size of the buffer to control the loop
		// if the buffer is not empty it will process the line
		if (size_buffer > 0)
		{
			size_buffer = 0;
			// Loop to find the position of the newline character
			while (buffer[fd][size_buffer] && buffer[fd][size_buffer] != '\n')
				size_buffer++;

			/*	flag to control the loop - it will be 0 if the newline character is found and 1 if not
				- if found (0), the loop will stop after processing the line
				- if not found (1), the loop will continue  */
			flag = (flag == size_buffer);

			/*	Update size_buffer with newline count
				- if the newline character is found the size_buffer will be incremented by 1 to include the newline character
				- if the newline character is not found the size_buffer will be incremented by 0 
			*/
			size_buffer += buffer[fd][size_buffer] == '\n';
			
			// process the line
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
