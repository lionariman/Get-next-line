/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keuclide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:38:28 by keuclide          #+#    #+#             */
/*   Updated: 2020/11/22 19:15:00 by keuclide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				check_count(int fd, char **line, char **rem, char *n)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*tmp;
	int			count;

	while (n == NULL && (count = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		if (count == -1)
			return (-1);
		buff[count] = '\0';
		if ((n = ft_strchr(buff, '\n')))
		{
			*n = '\0';
			*rem = ft_strdup(++n);
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
			*line = *rem;
			*rem = ft_strdup(++n);
		}
		else
		{
			*line = *rem;
			*rem = NULL;
		}
	}
	else
		*line = ft_mzero(1);
	return (n);
}

int				get_next_line(int fd, char **line)
{
	static char	*rem;
	char		*n;
	int			count;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if ((n = check_rem(line, &rem)) == NULL)
	{
		if ((count = check_count(fd, line, &rem, n)) < 0)
			return(-1);
	}
	if (rem || count)
		return (1);
	return (0);
}
