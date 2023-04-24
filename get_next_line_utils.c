/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:04:21 by jhogonca          #+#    #+#             */
/*   Updated: 2023/04/15 20:04:21 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_line(char *line, char *buffer,  long buffer_size, long *line_size)
{
    t_gnl g;

    g.line_size = -1;
    g.index = -1;
    g.buffer_size = -1;
    g.line = line;
    *line_size += buffer_size;
    line = malloc(sizeof(char) * (*line_size + 1));
    if (line)
    {
        line[*line_size] = 0;
        while (g.line && g.line[++g.line_size])
            line[++g.index] = g.line[*line_size];
        g.line_size = -1;
		while (buffer && buffer[++g.line_size])
		{
			if (g.line_size < buffer_size)
				line[++g.index] = buffer[g.line_size];
			else
				buffer[++g.buffer_size] = buffer[g.line_size];
			buffer[g.line_size] = 0;
		}
    }
	free(g.line);
	return (line);
}
