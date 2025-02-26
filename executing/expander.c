/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:38:40 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/26 20:42:27 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

bool	expander(t_exec *x, t_redir *r)
{
	int		fds[2];
	char	*line;

	line = NULL;
	if (pipe(fds) < 0)
		return (1);
	if (write(fds[WR_END], NULL, 0) < 0)
		return (print_error("minishell", "here_doc", "write error"), 1);
	while (1337)
	{
		line = get_next_line(r->fd);
		if (!line)
			break ;
		replaceenvar(x->lst, &line, x);
		write(fds[WR_END], line, ft_strlen(line));
	}
	(close(fds[WR_END]), close(r->fd), r->fd = fds[RD_END]);
	return (0);
}
