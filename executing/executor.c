/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:52:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/22 21:12:05 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	executor(t_node *head, t_env *env_lst)
{
	char	**env;

	if (!head)
		return ;
	env = envlsttoenv(env_lst);
	do_here_doc(head, env_lst);
	expand_cmds(head, env_lst);
	exec_(head, env);
	free_tree(head);
	freestrarr(&env);
	g_gb.ex_code = 0;
}
