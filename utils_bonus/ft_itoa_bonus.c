/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:39:46 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:12:06 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

static void	ft_putnbr_buff(int n, char *buff, int size, int pos)
{
	char			c;
	unsigned int	nb;

	nb = (unsigned int)n;
	if (n < 0)
	{
		buff[0] = '-';
		nb = ~0u - nb + 1;
		size += 1;
	}
	c = (nb % 10) + 48;
	if (nb / 10 != 0)
		ft_putnbr_buff(nb / 10, buff, size, pos + 1);
	buff[size - pos] = c;
}

char	*ft_itoa(int n)
{
	int		size;
	int		tmp;
	char	*buff;
	int		neg;

	tmp = n;
	size = 1;
	neg = 0;
	if (n < 0)
		neg = 1;
	while (tmp / 10)
	{
		size += 1;
		tmp /= 10;
	}
	buff = (char *)malloc(sizeof(char) * (size + neg + 1));
	if (!buff)
		return (NULL);
	ft_putnbr_buff(n, buff, size, 1);
	buff[size + neg] = 0;
	return (buff);
}
