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

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdlib.h>
# include	<fcntl.h>
# include   <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE   45
# endif

typedef struct s_line
{
	char	*line;
	long	size_line;
	long	index;
	long	size_buffer;
}	t_line;

static char	*get_line(char *line, char *buffer, long size_buffer, long *size_line)
{
	t_line	st;

	st.size_line = -1;
	st.index = -1;
	st.size_buffer = -1;
	st.line = line;
	*size_line += size_buffer;
	line = malloc(*size_line + 1 * sizeof(char));
	if (line)
	{
		line[*size_line] = 0;
		while (st.line && st.line[++st.size_line])
			line[++st.index] = st.line[st.size_line];
		st.size_line = -1;
		while (buffer && buffer[++st.size_line])
		{
			if (st.size_line < size_buffer)
				line[++st.index] = buffer[st.size_line];
			else
				buffer[++st.size_buffer] = buffer[st.size_line];
			buffer[st.size_line] = 0;
		}
	}
	free(st.line);
	return (line);
}

char	*get_next_line(int fd)
{
	t_line		st;
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];

	st.line = NULL;
	st.size_line = 0;
	st.size_buffer = 0;
	while (buf[fd][st.size_buffer] && fd >= 0 && fd < FOPEN_MAX)
		st.size_buffer++;
	st.index = 1;
	while (fd >= 0 && fd < FOPEN_MAX && st.index > 0)
	{
		if (!buf[fd][0] || !st.size_buffer)
			st.size_buffer = read(fd, buf[fd], BUFFER_SIZE);
		st.index = st.size_buffer;
		if (st.size_buffer > 0)
		{
			st.size_buffer = 0;
			while (buf[fd][st.size_buffer] && buf[fd][st.size_buffer] != '\n')
				st.size_buffer++;
			st.index = (st.index == st.size_buffer);
			st.size_buffer += buf[fd][st.size_buffer] == '\n';
			st.line = get_line(st.line, buf[fd], st.size_buffer, &st.size_line);
		}
		return (st.line);
	}
}

int main(int argc, char const *argv[])
{
	int fd;
	char *line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while (line = get_next_line(fd))
		{
			printf("%s", line);
			free(line);
		}
		close(fd);
	}
	return 0;
}
