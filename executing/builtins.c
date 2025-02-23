/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:54:22 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/23 18:55:13 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executing.h"

bool	builtins(t_node *head, t_exec *x)
{
	if (ft_strcmp("echo", head->args[0]) == 0)
		return (echo(head->args), 1);
	else if (ft_strcmp("export", head->args[0]) == 0)
	{
		_export(head->args, &x->lst);
		freestrarr(&x->env);
		x->env = envlsttoenv(x->lst);
		return (1);
	}
	else if (ft_strcmp("unset", head->args[0]) == 0)
	{
		unset(head->args, &x->lst);
		freestrarr(&x->env);
		x->env = envlsttoenv(x->lst);
		return (1);
	}
	else if (ft_strcmp("cd", head->args[0]) == 0)
		return (cd(head->args, &x->lst), 1);
	else if (ft_strcmp("exit", head->args[0]) == 0)
		return (exit_(head->args, 1), 1);
	else if (ft_strcmp("pwd", head->args[0]) == 0)
		return (pwd(), 1);
	else if (ft_strcmp("env", head->args[0]) == 0)
		return (env_(x->lst), 1);
	return (0);
}
