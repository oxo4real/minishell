/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:10:52 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 19:56:33 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd(char **av, t_env **env_lst)
{
	if (!av || !env_lst)
		return ;
	else if (!av[1] && !gohome(env_lst))
		return ;
	else if (av[1] && chdir(av[1]) != 0)
		return (print_error("minishell", "cd", av[1]));
	set_env(env_lst);
}

int	gohome(t_env **env_lst)
{
	t_env	*home;

	home = (*env_lst);
	while (home && ft_strcmp(home->key, "HOME") != 0)
		home = home->next;
	if (!home || !home->value)
		return (print_error2("minishell", "cd", NULL, "HOME not set"), 0);
	if (chdir(home->value) != 0)
		return (print_error("minishell", "cd", home->value), 0);
	return (1);
}

void	set_env(t_env **env_lst)
{
	t_env	*pwd;
	char	*newpwd;
	char	*av[3];

	av[2] = NULL;
	pwd = (*env_lst);
	while (pwd && ft_strcmp(pwd->key, "PWD") != 0)
		pwd = pwd->next;
	if (!pwd || !pwd->value)
		av[1] = ft_strdup("OLDPWD");
	else
		av[1] = ft_strjoin("OLDPWD", pwd->value, "=");
	_export(av, env_lst);
	free(av[1]);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		av[1] = ft_strdup("PWD");
	else
		av[1] = ft_strjoin("PWD", newpwd, "=");
	_export(av, env_lst);
	return (free(newpwd), free(av[1]));
}
