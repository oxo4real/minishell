/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:52:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:44:29 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing_bonus.h"

void	executor(t_node *head, t_exec *x)
{
	if (!head)
		return ;
	x->env = envlsttoenv(x->lst);
	g_sig = 1;
	if (do_here_doc(head, x))
		return ;
	exec_(head, x);
	free_tree(head);
	freestrarr(&x->env);
}
