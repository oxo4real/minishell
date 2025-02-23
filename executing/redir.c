/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:55:48 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/23 18:56:09 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static bool	handle_redir_helper(t_token tk, t_node *head, t_redir *r)
{
	if (tk == OUT || tk == APPEND)
	{
		close(head->fd[WR_END]);
		if (tk == APPEND)
			head->fd[WR_END] = open(r->filename, APPNED_MODE, 0777);
		else
			head->fd[WR_END] = open(r->filename, IN_MODE, 0777);
		if (head->fd[WR_END] < 0)
			return (1);
	}
	if (tk == IN || tk == HEREDOC)
	{
		close(head->fd[RD_END]);
		if (tk == HEREDOC)
			head->fd[RD_END] = r->fd;
		else
			head->fd[RD_END] = open(r->filename, O_RDONLY);
		if (head->fd[RD_END] < 0)
			return (1);
	}
	return (0);
}

bool	handle_redir(t_node *head, t_env *env_lst)
{
	t_redir	*r;
	char	*tmp;

	if (!head || !head->redir)
		return (0);
	r = head->redir;
	while (r)
	{
		replaceenvar(env_lst, &r->filename);
		tmp = polish_arg(r->filename);
		if (!tmp)
			return (1);
		free(r->filename);
		r->filename = tmp;
		if (handle_redir_helper(r->type, head, r))
			return (1);
		r = r->next;
	}
	return (0);
}
