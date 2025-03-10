/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:04:21 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/25 20:41:11 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	freenode(t_env **node);
static bool	valid_identifier(char *s, t_exec *x);

void	unset(char **av, t_env **env_lst, t_exec *x)
{
	t_env	*var;
	t_env	*head;
	int		i;

	x->status = 0;
	if (!env_lst || !av)
		return ;
	i = 0;
	while (av[++i])
	{
		var = (*env_lst);
		while (var && ft_strcmp(var->key, av[i]) != 0)
			var = var->next;
		if (var && valid_identifier(av[i], x))
		{
			head = (*env_lst);
			while (head != var && head->next != var)
				head = head->next;
			if (head == var)
				(*env_lst) = var->next;
			else
				head->next = var->next;
			freenode(&var);
		}
	}
}

static void	freenode(t_env **node)
{
	if (!node || !(*node))
		return ;
	free((*node)->key);
	free((*node)->value);
	free(*node);
	(*node) = NULL;
}

static bool	valid_identifier(char *s, t_exec *x)
{
	char	*str;

	str = s;
	if (!s || ft_isdigit(*s))
	{
		x->status = 1;
		return (print_error3("minishell", "export", str,
				"not a valid indentifier"), false);
	}
	while ((*s))
	{
		if (!ft_isalnum(*s) || (*s) == '_')
		{
			x->status = 1;
			return (print_error3("minishell", "export", str,
					"not a valid indentifier"), false);
		}
		s++;
	}
	return (true);
}
