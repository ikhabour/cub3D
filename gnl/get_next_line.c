/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 23:16:03 by ikhabour          #+#    #+#             */
/*   Updated: 2022/11/12 02:22:19 by ikhabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *save)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(save, '\n') && i)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(save);
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		save = ft_strjoin(save, buffer);
		if (!save)
			return (NULL);
	}
	free(buffer);
	return (save);
}

char	*first_line(char *save)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_strlen(save))
		return (NULL);
	i = search_nl(save, i);
	if (save[i] == '\n')
		line = malloc(sizeof(char) * i + 2);
	else
		line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	while (j <= i && save[j])
	{
		line[j] = save[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*second_line(char *save)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = search_nl(save, i);
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	i++;
	line = malloc(sizeof(char) * ft_strlen(save) - i + 1);
	if (!line)
	{
		free(save);
		return (NULL);
	}
	while (save[i])
		line[j++] = save[i++];
	line[j] = '\0';
	free(save);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	save = read_line(fd, save);
	if (!save)
		return (NULL);
	line = first_line(save);
	save = second_line(save);
	return (line);
}
