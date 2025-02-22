/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:10:51 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/22 21:11:01 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	expand_cmds(t_node *head, t_env *env_lst)
{
	if (!head)
		return ;
	if (head->type == STR)
		replaceenvar(env_lst, &head->cmd);
	expand_cmds(head->l_child, env_lst);
	expand_cmds(head->r_child, env_lst);
}
