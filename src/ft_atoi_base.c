/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:53:10 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/28 10:00:32 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strnchr(char *s, int c, int size)
{
	int	i;

	i = 0;
	while (size--)
	{
		if (c == s[i])
			return (i);
		i++;
	}
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	nbr;
	int	temp;
	int	aux;
	int	i;
	int	len;

	nbr = 0;
	temp = 0;
	aux = 0;
	i = -1;
	len = ft_strlen(str) - 1;
	while (str[++i])
	{
		if (ft_strnchr("0123456789ABCDEF", ft_toupper(str[i]), str_base) || \
			str[i] == '0')
		{
			temp = ft_strnchr("0123456789ABCDEF", ft_toupper(str[i]), str_base);
			aux = pow(str_base, len);
			nbr += temp * aux;
			len--;
		}
		else
			return (0);
	}
	return (nbr);
}
