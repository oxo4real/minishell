/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:09:36 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:10:49 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"

void	pwd(t_exec *x)
{
	char	*cwd;

	x->status = 0;
	if (write(1, NULL, 0) < 0)
	{
		x->status = 1;
		return (print_error("minishell", "pwd", "write error"));
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		x->status = 1;
		return (print_error("minishell", "pwd", NULL));
	}
	else
		return (printf("%s\n", cwd), free(cwd));
}
