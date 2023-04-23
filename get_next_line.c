/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 05:57:25 by jhogonca          #+#    #+#             */
/*   Updated: 2023/04/23 12:24:21 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_next_line(int fd)
{
	static char	buf[MAX][BUFFER_SIZE + 1];
	char		*line;
	int			readed;

	if (fd < 0 || MAX < fd || BUFFER_SIZE < 1)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	readed = 1;
	while (readed > 0)
	{
		line = ft_strjoin(line, buf[fd]);
		if (line == NULL)
			return (NULL);
		if (readed == -1)
		{
			free(line);
			return (NULL);
		}
		if (ft_save_line(buf[fd]))
			break ;
		readed = read(fd, buf[fd], BUFFER_SIZE);
	}
	return (line);
}
