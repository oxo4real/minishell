/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:10:51 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:11:39 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing_bonus.h"

void	expand_cmds(t_node *head, t_exec *x)
{
	if (!head)
		return ;
	if (head->type == STR)
		replaceenvar(x->lst, &head->cmd, x);
	expand_cmds(head->l_child, x);
	expand_cmds(head->r_child, x);
}
