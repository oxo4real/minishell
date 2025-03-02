/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:10:51 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/03/02 11:19:05 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing_bonus.h"

void	expand_cmds(t_node *head, t_exec *x)
{
	if (!head)
		return ;
	if (head->type == STR)
		replaceenvar(x->lst, &head->cmd, x, 1);
	expand_cmds(head->l_child, x);
	expand_cmds(head->r_child, x);
}
