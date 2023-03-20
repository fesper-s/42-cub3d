/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:54:44 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/20 09:56:00 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strrncmp(char *s1, char *s2, int len)
{
	int	size_s1;
	int size_s2;

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

void replace_char(char *str, char old, char new)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == old)
			str[i] = new;
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
	free(map->north);
	free(map->south);
	free(map->east);
	free(map->west);
	free(map->floor);
	free(map->ceiling);
}
