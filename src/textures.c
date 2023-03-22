/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:50:03 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/22 17:41:56 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			printf("entrou no if\n");
			while (ft_strncmp(line, "/* pixels */", 12))
			{
				aux = ft_strjoin(hex_line, line);
				//free(hex_line);
				hex_line = ft_strdup(aux);
				//free(aux);
				line = get_next_line(fd);
			}
			printf("saiu\n");
			break ;
		}
		line = get_next_line(fd);
	}
	hex_color = ft_split(hex_line, '\n');
	return (hex_color);
}

void	get_texture(void)
{
	int		fd;
	char	**hex_color;

	fd = open("./textures/bluestone.xpm", O_RDONLY);
	hex_color = get_hex_color(fd);
	printf("hex_color -> %s e %s\n", hex_color[0], hex_color[1]);
}
