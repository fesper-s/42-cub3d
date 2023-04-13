/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:30:47 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/13 08:45:26 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_info(int fd, t_map *map, int *j)
{
	char	*aux;
	char	*buffer;

	aux = get_next_line(fd);
	buffer = ft_strtrim(aux, "\n");
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
		map->map[(*j)++] = ft_strdup(buffer);
	free(buffer);
	free(aux);
}

int	assign_map(t_map *map, char *path, int map_len)
{
	int		i;
	int		j;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_error("File doesn't exist");
	i = -1;
	j = 0;
	while (++i < map_len)
		get_map_info(fd, map, &j);
	map->map[j] = 0;
	close(fd);
	return (0);
}

void	insert_fill_line(t_map *map, char ***b_map)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 1;
	while (map->map[++i])
	{
		(*b_map)[j] = ft_calloc((grand_line(map->map) + 3), sizeof(char));
		(*b_map)[j][0] = '3';
		ft_strlcat((*b_map)[j], map->map[i], grand_line(map->map) + 2);
		k = ft_strlen(map->map[i]);
		while (++k < grand_line(map->map) + 2)
			(*b_map)[j][k] = '3';
		(*b_map)[j][k] = 0;
		j++;
	}
}

int	read_map(char *path, t_map *map)
{
	int		map_len;
	int		i;

	i = -1;
	map_len = maplen(path);
	map->map = malloc(sizeof(char *) * (map_len + 1 - 6));
	assign_map(map, path, map_len);
	if (!check_sprites(map))
		return (0);
	check_map_elements(map);
	while (map->map[++i])
		replace_char(map->map[i], ' ', '3');
	map_validation(map);
	return (1);
}

int	check_map(char *path, t_map *map)
{
	if (ft_strrncmp(path, ".cub", 5))
		exit_error("Invalid type of file");
	init_map(map);
	read_map(path, map);
	return (0);
}
