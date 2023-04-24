/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:50:47 by jhogonca          #+#    #+#             */
/*   Updated: 2023/04/23 21:50:47 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stddef.h>

typedef struct s_gnl
{
	char	*line;
	long	index;
	long	read_bytes;
	long	buffer_size;
	long 	line_size;
} t_gnl;

char *get_next_line(int fd);
char    *get_line(char *line, char *buffer,  long buffer_size, long *line_size);


#endif
