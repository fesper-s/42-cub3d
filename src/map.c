/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:30:47 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/10 15:47:24 by fesper-s         ###   ########.fr       */
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
	int	len;

	i = -1;
	j = 1;
	while (map->map[++i])
	{
		len = ft_strlen(map->map[i]);
		(*b_map)[j] = malloc((len + 3) * sizeof(char));
		(*b_map)[j][0] = '3';
		ft_strlcat((*b_map)[j], map->map[i], len + 2);
		(*b_map)[j][len + 1] = '3';
		j++;
	}
}

void	map_validation(t_map *map)
{
	char	**b_map;
	int		len;
	int		i;
	int		k;

	printf("antes do len\n");
	len = 0;
	while (map->map[len])
		len++;
	b_map = malloc((len + 3) * sizeof(char *));

	printf("antes da primeira linha\n");
	b_map[0] = ft_strdup(map->map[0]);
	k = -1;
	while (b_map[0][++k])
		b_map[0][k] = '3';

	printf("antes de copiar o mapa\n");
	insert_fill_line(map, &b_map);

	printf("antes da ultima linha\n");
	b_map[len] = ft_strdup(map->map[len - 1]);
	k = -1;
	while (b_map[len][++k])
		b_map[len][k] = '3';

	printf("antes de printar o mapa\n");
	i = -1;
	while (b_map[++i])
		printf("%s\n", b_map[i]);
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
