/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:12:07 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/13 09:02:17 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int cub3d(char *map)
{
	if (ft_strrncmp(map, ".cub", 5))
		return (print_error("Invalid type of file"));
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (print_error("Invalid number of arguments"));
	cub3d(argv[1]);
	return (0);
}
