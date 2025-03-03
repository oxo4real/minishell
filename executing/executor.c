/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:52:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/03/03 12:28:06 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	executor(t_node *head, t_exec *x)
{
	if (!head)
		return ;
	x->env = envlsttoenv(x->lst);
	g_sig = 1;
	if (!do_here_doc(head, x))
		exec_(head, x);
	free_tree(head);
	freestrarr(&x->env);
}
