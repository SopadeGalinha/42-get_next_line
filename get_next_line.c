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

char *get_next_line(int fd)
{
	static char	bf[FOPEN_MAX][BUFFER_SIZE + 1];
	t_gnl		gnl;

	gnl.line = NULL;
	gnl.index = 1;
	gnl.read_bytes = 0;
	gnl.buffer_size = 0;

	while (fd >= 0 && fd < FOPEN_MAX && bf[fd][gnl.buffer_size])
		gnl.buffer_size++;
	gnl.line_size = 0;
	
	while (fd >= 0 && fd < FOPEN_MAX && gnl.index > 0)
	{
		if (gnl.buffer_size == 0 || bf[fd][0] == '\0')
			gnl.buffer_size = read(fd, bf[fd], BUFFER_SIZE);
		gnl.index = gnl.buffer_size;
		if (gnl.buffer_size > 0)
		{
			gnl.buffer_size = 0;
			while (fd >= 0 && bf[fd][gnl.buffer_size] && bf[fd][gnl.buffer_size] != '\n')
					gnl.buffer_size++;
			gnl.index = (gnl.index == gnl.buffer_size);
			gnl.buffer_size += bf[fd][gnl.buffer_size] == '\n';
			gnl.line = get_line(gnl.line, bf[fd],  gnl.buffer_size, &gnl.line_size);
		}
	}
	return (gnl.line);
}
