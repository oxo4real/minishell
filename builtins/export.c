/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:22:37 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/07 13:28:48 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int			ft_strcmp(const char *s1, const char *s2);
char		**split_var(char *var);
int			expandenvlst(t_env **env_lst, char	**splited);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2, char const *sep);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
void		pexport(t_env *env_lst);
void		print_error3(char *shell_name, char *command,
			char *details, char *description);

static void	replace(t_env *var, char ***splited);
static void	append(t_env *var, char ***splited);
static void	addtolst(t_env **env_lst, char ***splited, char *has_value);
static bool	valid_identifier(char *s);

void	export(char **av, t_env **env_lst)
{
	t_env	*var;
	t_env	*head;
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
		else if (*(ft_strchr(av[i], '=') - 1) == '+')
			append(var, &splited);
		else
			replace(var, &splited);
	}
}

static void	replace(t_env *var, char ***splited)
{
	free(var->value);
	var->value = (*splited)[1];
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
