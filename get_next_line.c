/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:38:28 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/20 12:05:23 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			ft_strcpy(char *d, char *s)
{
	int			i;

	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

int				qnl(int fd, char *buff, char **line, char **rem)
{
	char		*tmp;
	char		*n;
	int			count;

	n = NULL;
	while (n == NULL && (count = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[count] = '\0';
		if ((n = ft_strchr(buff, '\n')) != NULL)
		{
			*n = '\0';
			n++;
			*rem = ft_strdup(n);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp);
	}
	return (count);
}

char			*check_rem(char **line, char **rem)
{
	char		*n;

	n = NULL;
	if (*rem != NULL)
	{
		if ((n = ft_strchr(*rem, '\n')))
		{
			*n = '\0';
			*line = ft_strdup(*rem);
			n++;
			ft_strcpy(*rem, n);
		}
		else
		{
			*line = ft_strdup(*rem);
			free(*rem);
		}
	}
	else
		*line = ft_mzero(1);
	return (n);
}

int				get_next_line(int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*rem;
	int			count;

	if (check_rem(line, &rem) == NULL)
		count = qnl(fd, buff, line, &rem);
	if (ft_strlen(*line) || count)
		return (1);
	else
		return (0);
}
