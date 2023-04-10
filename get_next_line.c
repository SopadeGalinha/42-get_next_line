/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:27:31 by jhogonca          #+#    #+#             */
/*   Updated: 2023/04/09 17:27:31 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

char	*ft_strchr(const char *s, int c)
{
	while (*s && (unsigned char)c != *s)
		s++;
	if ((unsigned char)c == *s)
		return ((char *)s);
	return (0);
}

static int	ft_clean(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	while (str[i])
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (1);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	free((char *)s1);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	size_t		read_size;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	line = (char *)malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (1)
	{
		if (buf[fd][0] == '\0')
		{
			read_size = read(fd, buf[fd], BUFFER_SIZE);
			if (read_size <= 0)
				break ;
			buf[fd][read_size] = '\0';
		}
		line = ft_strjoin(line, buf[fd]);
		if (line == NULL)
			return (NULL);
		if (ft_strchr(buf[fd], '\n') != NULL)
			break ;
		buf[fd][0] = '\0';
	}
	if (read_size == 0 && ft_strlen(line) == 0)
	{
		free(line);
		line = NULL;
	}
	else
		ft_clean(buf[fd]);
	return (line);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	*text;

	if (argc < 1)
		return (printf("Please provide a filename as an argument\n"));
	// text = argv[argc - 1];
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
