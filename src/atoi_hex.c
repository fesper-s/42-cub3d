/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:53:10 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/23 12:06:13 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_strnchr(char *s, int c, int size)
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

static char	to_upper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

static int	to_power(int nbr, int power)
{
	int	result;

	result = 1;
	if (power == 0)
		return (1);
	if (power == 1)
		return (nbr);
	while (power--)
		result *= nbr;
	return (result);
}

int	atoi_hex(const char *str, int i, int len, long nbr)
{
	int		temp;
	int		temp2;
	int		sign;

	temp = 0;
	temp2 = 0;
	sign = 1;
	while (str[++i])
	{
		if (ft_strnchr("0123456789ABCDEF", to_upper(str[i]), 16) || \
			str[i] == '0')
		{
			temp = ft_strnchr("0123456789ABCDEF", to_upper(str[i]), 16);
			temp2 = to_power(16, len);
			nbr += temp * temp2;
			len--;
		}
		else
			return (0);
	}
	return (sign * nbr);
}
