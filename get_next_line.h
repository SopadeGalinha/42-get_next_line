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

# include	<fcntl.h>
# include   <stdio.h>
# include	<stdlib.h>
# include	<unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE   1331
# endif

char	*get_next_line(int fd);

#endif
