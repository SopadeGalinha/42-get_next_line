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

char	*get_next_line(int fd)
{
	static char	f[FOPEN_MAX][BUFFER_SIZE + 1];
	t_line		d;

	d.line = NULL;
	d.size_buffer = 0;
	d.index = 1;
	while (fd >= 0 && fd < FOPEN_MAX && f[fd][d.size_buffer])
		d.size_buffer++;
	d.size_line = 0;
	while (fd >= 0 && fd < FOPEN_MAX && d.index > 0)
	{
		if (!f[fd][0] || !d.size_buffer)
			d.size_buffer = read(fd, f[fd], BUFFER_SIZE);
		d.index = d.size_buffer;
		if (d.size_buffer > 0)
		{
			d.size_buffer = 0;
			while (f[fd][d.size_buffer] && f[fd][d.size_buffer] != '\n')
				d.size_buffer++;
			d.index = (d.index == d.size_buffer);
			d.size_buffer += f[fd][d.size_buffer] == '\n';
			d.line = get_line(d.line, f[fd], d.size_buffer, &d.size_line);
		}
	}
	return (d.line);
}
