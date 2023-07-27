/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebbaill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:10:12 by sebbaill          #+#    #+#             */
/*   Updated: 2020/02/13 18:44:18 by sebbaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_read(char *save, int fd, int *head)
{
	char			buf[BUFFER_SIZE + 1];
	char			*tmp;

	while ((*head = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[*head] = '\0';
		if (!save)
			save = ft_strdup(buf);
		else
		{
			tmp = save;
			save = ft_strjoin(save, buf);
			free(tmp);
		}
		if (ft_strchr(save, '\n'))
			break ;
	}
	return (save);
}

static int	save_to_line(char *save, char **line)
{
	int				i;

	i = 0;
	if (save)
	{
		while (save[i] != '\0' && save[i] != '\n')
			i++;
		if (save[i] == '\n')
		{
			*line = ft_substr(save, 0, i);
			return (1);
		}
		else
		{
			*line = ft_strdup(save);
			return (0);
		}
	}
	else
	{
		*line = ft_strdup("");
		return (0);
	}
}

static char	*get_the_rest(char *save)
{
	int				i;
	int				save_len;
	char			*tmp;

	i = 0;
	save_len = ft_strlen(save);
	if (save)
	{
		while (save[i] != '\0' && save[i] != '\n')
			i++;
		if (save[i] == '\n')
		{
			tmp = save;
			save = ft_substr(save, i + 1, save_len - i - 1);
			free(tmp);
		}
	}
	return (save);
}

int	get_next_line(int fd, char **line)
{
	int				head;
	static char		*save[1024];
	int				rest;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	save[fd] = get_read(save[fd], fd, &head);
	if (head < 0)
		return (-1);
	rest = save_to_line(save[fd], line);
	if (rest)
		save[fd] = get_the_rest(save[fd]);
	else
	{
		free(save[fd]);
		save[fd] = NULL;
		return (0);
	}
	return (1);
}
