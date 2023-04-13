/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:54:44 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/13 08:19:22 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strrncmp(char *s1, char *s2, int len)
{
	int	size_s1;
	int	size_s2;

	if (!len)
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	while (len)
	{
		if (s1[size_s1] != s2[size_s2])
			return (s1[size_s1] - s2[size_s2]);
		size_s1--;
		size_s2--;
		len--;
	}
	return (0);
}

void	replace_char(char *str, char old, char new)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == old)
			str[i] = new;
	}
}

int	char_in_str(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

int	maplen(char *path)
{
	int		len;
	int		fd;
	char	*aux;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_error("File doesn't exist");
	len = 0;
	aux = get_next_line(fd);
	while (aux)
	{
		free(aux);
		aux = get_next_line(fd);
		len++;
	}
	free(aux);
	close(fd);
	return (len);
}

int	grand_line(char **str)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if ((int)ft_strlen(str[i]) > len)
			len = ft_strlen(str[i]);
	}
	return (len);
}
