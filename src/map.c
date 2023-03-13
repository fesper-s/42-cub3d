/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:30:47 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/13 12:14:45 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	maplen(char *path)
{
	int	len;
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("File doesn't exist"));
	len = 0;
	while (get_next_line(fd))
		len++;
	return (len);
}

int	read_map(char *path)
{
	int		fd;
	char	**map;
	int		map_len;
	int		i;

	map_len = maplen(path);
	map = malloc(sizeof(char *) * (map_len + 1));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("File doesn't exist"));
	i = -1;
	while (++i < map_len)
		map[i] = ft_strtrim(get_next_line(fd), "\n");
	map[i] = "\0";
	i = -1;
	while (++i < map_len)
		printf("%s\n", map[i]);
	return (0);
}

int	check_map(char *path)
{
	if (ft_strrncmp(path, ".cub", 5))
		return (print_error("Invalid type of file"));
	read_map(path);
	return (0);
}
