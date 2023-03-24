/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:50:03 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/24 14:35:24 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*check_line(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = malloc(sizeof(char) * 8);
	i = -1;
	j = -1;
	while (line[++i])
	{
		while ((line[i] == ' ' || line[i] == 'c' || line[i] == '#' || \
			line[i] == '\"' || line[i] == ',') && i != 1)
			i++;
		new_line[++j] = line[i];
	}
	new_line[j + 1] = 0;
	free(line);
	return (new_line);
}

char	**get_hex_color(int fd)
{
	char	**hex_color;
	char	*line;
	char	*hex_line;
	char	*aux;

	hex_line = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "\"  c #000000\",", 14))
		{
			while (ft_strncmp(line, "/* pixels */", 12))
			{
				line = check_line(line);
				aux = ft_strjoin(hex_line, line);
				//free(hex_line);
				hex_line = ft_strdup(aux);
				//free(aux);
				//free(line);
				line = get_next_line(fd);
			}
			break ;
		}
		//free(line);
		line = get_next_line(fd);
	}
	hex_color = ft_split(hex_line, '\n');
	//free(hex_line);
	return (hex_color);
}

static char	*check_texture_line(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	if (line[ft_strlen(line) - 1] == ',')
		new_line = malloc(sizeof(char) * (ft_strlen(line) - 3 + 1));
	else
		new_line = malloc(sizeof(char) * (ft_strlen(line) - 2 + 1));
	i = -1;
	j = -1;
	while (line[++i])
	{
		while (i == 0 || i == (int) ft_strlen(line) - 2 || \
			(i == (int) ft_strlen(line) - 3 && \
			line[ft_strlen(line) - 2] == ','))
			i++;
		new_line[++j] = line[i];
	}
	new_line[j + 1] = 0;
	//free(line);
	return (new_line);
}

char	**get_texture_line(int fd)
{
	char	*line;
	char	*aux;
	char	*buffer;
	char	**texture_line;

	buffer = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "/* pixels */", 12))
		{
			line = get_next_line(fd);
			while (ft_strncmp(line, "};", 2))
			{
				line = check_texture_line(line);
				aux = ft_strjoin(buffer, line);
				//free(buffer);
				buffer = ft_strdup(aux);
				//free(aux);
				//free(line);
				line = get_next_line(fd);
			}
			break ;
		}
		//free(line);
		line = get_next_line(fd);
	}
	texture_line = ft_split(buffer, '\n');
	//free(buffer);
	return (texture_line);
}

int	**convert_texture(char **texture_line, char **hex_color)
{
	int		**texture;
	char	*texture_char;
	char	**buffer;
	int		i;
	int		j;

	i = 0;
	j = -1;
	texture = malloc(sizeof(int *) * 64);
	buffer = hex_color;
	while (*texture_line)
	{
		texture_char = *texture_line;
		while (*texture_char)
		{
			hex_color = buffer;
			while (*hex_color)
			{
				if (*texture_char == *hex_color[0])
				{
					while (++j <= 64)
					{
						if (j == 64)
						{
							j = 0;
							i++;
						}
						printf("antes do atoi_hex\n");
						texture[i][j] = atoi_hex(&(*hex_color)[1], -1, \
							ft_strlen(&(*hex_color)[1]), 0);
						printf("depois do atoi_hex\n");
						printf("%d\n", texture[i][j]);
					}
				}
				hex_color++;
			}
			texture_char++;
		}
		texture_line++;
	}
	printf("return\n");
	return (texture);
}

int	**get_texture(void)
{
	int		fd;
	char	**hex_color;
	char	**texture_line;
	int		**texture;

	fd = open("./textures/bluestone.xpm", O_RDONLY);
	hex_color = get_hex_color(fd);
	close(fd);
	fd = open("./textures/bluestone.xpm", O_RDONLY);
	texture_line = get_texture_line(fd);
	close(fd);
	texture = convert_texture(texture_line, hex_color);
	free_charpp(hex_color);
	free_charpp(texture_line);
	return (texture);
}
