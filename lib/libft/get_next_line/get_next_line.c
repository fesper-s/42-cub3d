/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:50:20 by fesper-s          #+#    #+#             */
/*   Updated: 2022/06/13 14:02:26 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *holder)
{
	char	*buffer;
	int		b_size;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	b_size = 1;
	while (!ft_strchr(holder, '\n') && b_size)
	{
		b_size = read(fd, buffer, BUFFER_SIZE);
		if (b_size == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[b_size] = '\0';
		if (!holder)
		{
			holder = malloc(1 * sizeof(char));
			*holder = '\0';
		}
		holder = ft_strjoin(holder, buffer);
	}
	free(buffer);
	return (holder);
}

static char	*get_line(char *holder)
{
	char	*str;
	size_t	len;

	len = 0;
	if (!holder[len])
		return (NULL);
	while (holder[len] && holder[len] != '\n')
		len++;
	str = malloc((len + 2) * sizeof(char));
	if (!str)
		return (NULL);
	len = 0;
	while (holder[len] && holder[len] != '\n')
	{
		str[len] = holder[len];
		len++;
	}
	if (holder[len] == '\n')
		str[len++] = '\n';
	str[len] = '\0';
	return (str);
}

static char	*hold_line(char *holder)
{
	size_t	len;
	size_t	i;
	char	*str;

	len = 0;
	while (holder[len] && holder[len] != '\n')
		len++;
	if (!holder[len])
	{
		free(holder);
		return (NULL);
	}
	str = malloc((ft_strlen(holder) - len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	len++;
	i = 0;
	while (holder[len])
		str[i++] = holder[len++];
	str[i] = '\0';
	free(holder);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*holder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	holder = read_line(fd, holder);
	if (!holder)
		return (NULL);
	buffer = get_line(holder);
	holder = hold_line(holder);
	return (buffer);
}
