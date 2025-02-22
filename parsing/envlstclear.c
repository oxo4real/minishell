/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:09:34 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 20:18:26 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	envlstclear(t_env **env_lst)
{
	t_env	*tmp;

	if (!env_lst || !(*env_lst))
		return ;
	while ((*env_lst))
	{
		free((*env_lst)->key);
		free((*env_lst)->value);
		tmp = (*env_lst);
		(*env_lst) = (*env_lst)->next;
		free(tmp);
	}
	(*env_lst) = NULL;
}
