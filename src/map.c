/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:30:47 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/17 12:20:33 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	asign_map_info(char *str, char *to_cmp, t_map *map, int *found_map)
{
	char	*buffer;

	if (*found_map == 1)
		exit_error("Map should be last element");
	buffer = ft_strtrim(str + ft_strlen(to_cmp), " ");
	if (!ft_strncmp(to_cmp, "NO ", 3))
		map->north = ft_strdup(buffer);
	else if (!ft_strncmp(to_cmp, "SO ", 3))
		map->south = ft_strdup(buffer);
	else if (!ft_strncmp(to_cmp, "EA ", 3))
		map->east = ft_strdup(buffer);
	else if (!ft_strncmp(to_cmp, "WE ", 3))
		map->west = ft_strdup(buffer);
	else if (!ft_strncmp(to_cmp, "F ", 2))
		map->floor = ft_strdup(buffer);
	else if (!ft_strncmp(to_cmp, "C ", 2))
		map->ceiling = ft_strdup(buffer);
	free(buffer);
}

void	get_map_info(int fd, t_map *map, int *j, int *found_map)
{
	char	*aux;
	char	*buffer;

	aux = get_next_line(fd);
	buffer = ft_strtrim(aux, "\n");
	if (!ft_strncmp(buffer, "NO ", 3))
		asign_map_info(buffer, "NO ", map, found_map);
	else if (!ft_strncmp(buffer, "SO ", 3))
		asign_map_info(buffer, "SO ", map, found_map);
	else if (!ft_strncmp(buffer, "EA ", 3))
		asign_map_info(buffer, "EA ", map, found_map);
	else if (!ft_strncmp(buffer, "WE ", 3))
		asign_map_info(buffer, "WE ", map, found_map);
	else if (!ft_strncmp(buffer, "F ", 2))
		asign_map_info(buffer, "F ", map, found_map);
	else if (!ft_strncmp(buffer, "C ", 2))
		asign_map_info(buffer, "C ", map, found_map);
	else if (ft_strlen(buffer) && buffer[0])
	{
		*found_map = 1;
		map->map[(*j)++] = ft_strdup(buffer);
	}
	else if (*found_map == 1)
		exit_error("Found empty line inside map");
	free_two(buffer, aux);
}

int	assign_map(t_map *map, char *path, int map_len)
{
	int		i;
	int		j;
	int		fd;
	int		found_map;

	found_map = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_error("File doesn't exist");
	i = -1;
	j = 0;
	while (++i < map_len)
		get_map_info(fd, map, &j, &found_map);
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
	check_sprites(map);
	check_map_elements(map);
	while (map->map[++i])
		replace_char(map->map[i], ' ', '3');
	map_validation(map);
	return (1);
}
