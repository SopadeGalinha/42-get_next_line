/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:00:37 by jhogonca          #+#    #+#             */
/*   Updated: 2023/04/25 19:00:37 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

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
