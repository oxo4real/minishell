/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandenvlst_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:17:59 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:11:17 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	expandenvlst(t_env **env_lst, char **splited)
{
	t_env	*new;
	t_env	*head;

	if (!env_lst || !splited)
		return (0);
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = splited[0];
	new->value = splited[1];
	new->next = NULL;
	if (!(*env_lst))
		(*env_lst) = new;
	else
	{
		head = (*env_lst);
		while (head->next)
			head = head->next;
		head->next = new;
	}
	return (1);
}
