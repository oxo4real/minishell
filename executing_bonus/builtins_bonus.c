/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:54:22 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:10:49 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"

bool	builtins(t_node *head, t_exec *x)
{
	if (ft_strcmp("echo", head->args[0]) == 0)
		return (echo(head->args, x), 1);
	else if (ft_strcmp("export", head->args[0]) == 0)
	{
		_export(head->args, &x->lst, x);
		freestrarr(&x->env);
		return (x->env = envlsttoenv(x->lst), 1);
	}
	else if (ft_strcmp("unset", head->args[0]) == 0)
	{
		unset(head->args, &x->lst, x);
		freestrarr(&x->env);
		return (x->env = envlsttoenv(x->lst), 1);
	}
	else if (ft_strcmp("cd", head->args[0]) == 0)
		return (cd(head->args, &x->lst, x), 1);
	else if (ft_strcmp("exit", head->args[0]) == 0)
		return (exit_(head->args, isatty(STDIN_FILENO), x), 1);
	else if (ft_strcmp("pwd", head->args[0]) == 0)
		return (pwd(x), 1);
	else if (ft_strcmp("env", head->args[0]) == 0)
		return (env_(x->lst, x), 1);
	return (0);
}
