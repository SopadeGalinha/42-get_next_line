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

char	*get_line(char *line, char *buffer, long size_buffer, long *size_line)
{
	t_line	data;

	data.size_line = -1;
	data.index = -1;
	data.size_buffer = -1;
	data.line = line;
	*size_line += size_buffer;
	line = malloc(*size_line + 1 * sizeof(char));
	if (line)
	{
		line[*size_line] = 0;
		while (data.line && data.line[++data.size_line])
			line[++data.index] = data.line[data.size_line];
		data.size_line = -1;
		while (buffer && buffer[++data.size_line])
		{
			if (data.size_line < size_buffer)
				line[++data.index] = buffer[data.size_line];
			else
				buffer[++data.size_buffer] = buffer[data.size_line];
			buffer[data.size_line] = 0;
		}
	}
	free(data.line);
	return (line);
}
