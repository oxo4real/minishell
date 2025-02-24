/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:52:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/24 21:35:53 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

void	executor(t_node *head, t_exec *x)
{
	if (!head)
		return ;
	x->status = 0;
	x->env = envlsttoenv(x->lst);
	if (do_here_doc(head, x->lst))
		return ;
	g_sig = 1;
	exec_(head, x);
	free_tree(head);
	freestrarr(&x->env);
}
