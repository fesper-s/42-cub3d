/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:30:47 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/20 10:04:35 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	maplen(char *path)
{
	int		len;
	int		fd;
	char	*aux;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("File doesn't exist"));
	len = 0;
	aux = get_next_line(fd);
	while (aux)
	{
		aux = get_next_line(fd);
		len++;
	}
	free(aux);
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
	j = 0;
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
		else if (!ft_strncmp(buffer, "F ", 2))
			map->floor = ft_strtrim(buffer + 1, " ");
		else if (!ft_strncmp(buffer, "C ", 2))
			map->ceiling = ft_strtrim(buffer + 1, " ");
		else if (ft_strlen(buffer) && buffer[0])
			map_ptr[0][j++] = ft_strdup(buffer);
		free(buffer);
	}
	map_ptr[0][j] = 0;
	close(fd);
	return (0);
}

int	read_map(char *path, t_map *map)
{
	char	**map_ptr;
	int		map_len;
	int		i = -1;

	map_len = maplen(path);
	map_ptr = malloc(sizeof(char *) * (map_len + 1 - 6));
	assign_map(map, &map_ptr, path, map_len);
	if (!check_sprites(map))
		return (0);
	while (map_ptr[++i])
		replace_char(map_ptr[i], ' ', '1');
	map->map = map_ptr;
	return (1);
}

int	check_map(char *path, t_map *map)
{
	if (ft_strrncmp(path, ".cub", 5))
		return (print_error("Invalid type of file"));
	read_map(path, map);
	return (0);
}
