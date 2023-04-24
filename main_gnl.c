/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:49:36 by jhogonca          #+#    #+#             */
/*   Updated: 2023/04/23 21:49:36 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	*text;

	if (argc < 1)
		return (printf("Please provide a filename as an argument\n"));
	text = "file.txt";
	fd = open(text, O_RDONLY);
	if (fd == -1)
		return (printf("Could not open file\n"));
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
