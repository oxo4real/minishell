/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:52:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/23 18:27:35 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

void	executor(t_node *head, t_exec *x)
{
	if (!head)
		return ;
	x->status = 0;
	x->fd[RD_END] = -42;
	x->fd[WR_END] = -42;
	x->env = envlsttoenv(x->lst);
	if (do_here_doc(head, x->lst))
		return ;
	exec_(head, x);
	free_tree(head);
	freestrarr(&x->env);
	x->status = 0;
}
