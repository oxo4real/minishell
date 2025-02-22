/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:07:51 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 20:18:26 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**alloc_rendu(char *var);

char	**split_var(char *var)
{
	char	**rendu;
	int		start;
	int		count;

	count = -1;
	rendu = alloc_rendu(var);
	if (!rendu)
		return (NULL);
	while (var[++count] && var[count] != '+' && var[count] != '=')
		rendu[0][count] = var[count];
	rendu[0][count] = '\0';
	start = count;
	if (var[count] == '+')
		start = count + 2;
	else if (var[count])
		start = count + 1;
	count = 0;
	while (var[start + count])
	{
		rendu[1][count] = var[start + count];
		count++;
	}
	rendu[1][count] = '\0';
	return (rendu);
}

static char	**alloc_rendu(char *var)
{
	int		start;
	int		count;
	char	**rendu;

	rendu = malloc(sizeof(char *) * 2);
	if (!rendu)
		return (NULL);
	count = 0;
	while (var[count] && var[count] != '+' && var[count] != '=')
		count++;
	rendu[0] = malloc(sizeof(char) * (count + 1));
	if (!rendu[0])
		return (free(rendu), NULL);
	start = count;
	if (var[count] == '+')
		start = count + 2;
	else if (var[count])
		start = count + 1;
	count = 0;
	while (var[start + count])
		count++;
	rendu[1] = malloc(sizeof(char) * (count + 1));
	if (!rendu[1])
		return (free(rendu[0]), free(rendu), NULL);
	return (rendu);
}
