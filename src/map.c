/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:30:47 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/13 14:01:15 by fesper-s         ###   ########.fr       */
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
	close(fd);
	return (len);
}

void	init_map(t_map *map)
{
	map->north = NULL;
}

int assign_map(t_map *map, char ***map_ptr, char *path, int map_len)
{
	int		i;
	int		j;
	int		fd;
	char	*buffer;

	init_map(map);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("File doesn't exist"));
	i = -1;
	j = -1;
	while (++i < map_len)
	{
		buffer = ft_strtrim(get_next_line(fd), "\n");
		if (!ft_strncmp(buffer, "NO ", 3))
			map->north = ft_strtrim(buffer + 2, " ");
		else if (!ft_strncmp(buffer, "SO ", 3))
			map->south = ft_strtrim(buffer + 2, " ");
		else if (!ft_strncmp(buffer, "EA ", 3))
			map->east = ft_strtrim(buffer + 2, " ");
		else if (!ft_strncmp(buffer, "WE ", 3))
			map->west = ft_strtrim(buffer + 2, " ");
		else
			map_ptr[0][++j] = ft_strdup(buffer);
		free(buffer);
	}
	map_ptr[0][j] = "\0";
	close(fd);
	return (0);
}

int	read_map(char *path, t_map *map)
{
	char	**map_ptr;
	int		map_len;
	int		i;

	map_len = maplen(path);
	map_ptr = malloc(sizeof(char *) * (map_len + 1 - 4));
	assign_map(map, &map_ptr, path, map_len);
	i = -1;
	while (++i < map_len - 4)
		printf("%s\n", map_ptr[i]);
	return (0);
}

int	check_map(char *path, t_map *map)
{
	if (ft_strrncmp(path, ".cub", 5))
		return (print_error("Invalid type of file"));
	read_map(path, map);
	return (0);
}
