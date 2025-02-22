/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:58:45 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 18:50:32 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_longlen(char *w);

int	ft_islong(char *w)
{
	int	int_len;
	int	i;

	i = 0;
	int_len = ft_longlen(w);
	while (w[i] == '0' || w[i] == ' ' || w[i] == '-' || w[i] == '+')
		i++;
	if (int_len < 0)
	{
		if (int_len < -19)
			return (0);
		else if (int_len == -19 && ft_wordcmp(&w[i], "9223372036854775808") > 0)
			return (0);
	}
	else
	{
		if (int_len > 19)
			return (0);
		else if (int_len == 19 && ft_wordcmp(&w[i], "9223372036854775807") > 0)
			return (0);
	}
	return (1);
}

static int	ft_longlen(char *w)
{
	int	i;
	int	count;
	int	signe;

	i = 0;
	count = 0;
	signe = 1;
	while (w[i] == ' ' || w[i] == '0' || w[i] == '-' || w[i] == '+')
	{
		if (w[i] == '-')
			signe *= -1;
		i++;
	}
	while (w[i] && w[i] != ' ')
	{
		i++;
		count++;
	}
	return (count * signe);
}
