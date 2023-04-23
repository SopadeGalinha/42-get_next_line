/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 05:32:22 by jhogonca          #+#    #+#             */
/*   Updated: 2023/04/23 12:24:08 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_save_line(char *buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!ft_strchr(buf, '\n'))
		return (0);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	while (buf[i] != '\0')
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	buf[j] = '\0';
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *line, char const *buf)
{
	char	*new;
	int		i;
	int		j;

	if (!line || !buf)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
		i++;
	while (buf[j] && buf[j] != '\n')
		j++;
	new = malloc(sizeof(char) * (i + j + 1));
	if (new == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (line[++i])
		new[i] = line[i];
	while (buf[++j] && buf[j] != '\n')
		new[i++] = buf[j];
	new[i] = '\0';
	return (new);
}
