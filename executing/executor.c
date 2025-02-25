/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:52:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/25 19:58:31 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	executor(t_node *head, t_exec *x)
{
	if (!head)
		return ;
	x->status = 0;
	x->env = envlsttoenv(x->lst);
	if (do_here_doc(head, x->lst, x))
		return ;
	g_sig = 1;
	exec_(head, x);
	free_tree(head);
	freestrarr(&x->env);
}
