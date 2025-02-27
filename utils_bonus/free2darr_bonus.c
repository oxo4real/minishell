/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2darr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:42:43 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:12:06 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	freestrarr(char ***arr)
{
	int	i;

	i = 0;
	if (!arr || !(*arr))
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free((*arr));
	(*arr) = NULL;
}
