/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sptobel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:46:07 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 20:18:26 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	skipquote(int *i, char *str);

void	sptobel(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			skipquote(&i, str);
		else if (str[i] == ' ')
			str[i] = '\x07';
		i++;
	}
}

static void	skipquote(int *i, char *str)
{
	char	quote;

	quote = str[(*i)++];
	while ((*i) > -1 && str[*i] != quote)
		(*i)++;
}
