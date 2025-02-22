/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:22:37 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 19:56:20 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	replace(t_env *var, char ***splited, char *has_value);
static void	append(t_env *var, char ***splited);
static void	addtolst(t_env **env_lst, char ***splited, char *has_value);
static bool	valid_identifier(char *s);

void	_export(char **av, t_env **env_lst)
{
	t_env	*var;
	char	**splited;
	int		i;

	if (!av[1])
		return (pexport(*env_lst));
	i = 0;
	while (av[++i])
	{
		if (!valid_identifier(av[i]))
			continue ;
		splited = split_var(av[i]);
		if (!splited)
			continue ;
		var = (*env_lst);
		while (var && ft_strcmp(var->key, splited[0]) != 0)
			var = var->next;
		if (!var)
			addtolst(env_lst, &splited, ft_strchr(av[i], '='));
		else if (ft_strchr(av[i], '=') && *(ft_strchr(av[i], '=') - 1) == '+')
			append(var, &splited);
		else
			replace(var, &splited, ft_strchr(av[i], '='));
	}
}

static void	replace(t_env *var, char ***splited, char *has_value)
{
	if (has_value)
	{
		free(var->value);
		var->value = (*splited)[1];
	}
	else
		free((*splited)[1]);
	free((*splited)[0]);
	free((*splited));
	(*splited) = NULL;
}

static void	addtolst(t_env **env_lst, char ***splited, char *has_value)
{
	if (!has_value)
	{
		free((*splited)[1]);
		(*splited)[1] = NULL;
	}
	expandenvlst(env_lst, (*splited));
	free(*splited);
	(*splited) = NULL;
}

static bool	valid_identifier(char *s)
{
	char	*str;

	str = s;
	if (!s || (*s) == '+' || (*s) == '=' || ft_isdigit(*s))
		return (print_error3("minishell", "export", str,
				"not a valid indentifier"), false);
	while ((*s) && (*s) != '+' && (*s) != '=')
	{
		if (!ft_isalnum(*s) && (*s) != '_')
			return (print_error3("minishell", "export", str,
					"not a valid indentifier"), false);
		s++;
	}
	if ((*s) == '+' && (*(s + 1)) != '=')
		return (print_error3("minishell", "export", str,
				"not a valid indentifier"), false);
	return (true);
}

static void	append(t_env *var, char ***splited)
{
	char	*new_value;

	new_value = ft_strjoin(var->value, (*splited)[1], "");
	free(var->value);
	var->value = new_value;
	free((*splited)[0]);
	free((*splited)[1]);
	free((*splited));
	(*splited) = NULL;
}
