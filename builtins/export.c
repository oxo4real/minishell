/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:22:37 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/06 14:00:28 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	modify(t_env *var, char ***splited);
static void	add(t_env **env_lst, char ***splited);
static void freesplited(char ***splited);

void	export(char **av, t_env **env_lst)
{
	t_env	*var;
	t_env	*head;
	char	**splited;
	int		i;

	if (!env_lst || !av)
		return ;
	i = 0;
	while (av[++i])
	{
		splited = split_var(av[i]);
		if (!splited || !ft_strchr(av[i], '='))
		{
			freesplited(&splited);
			continue ;
		}
		var = (*env_lst);
		while (var && ft_strcmp(var->key, splited[0]) != 0)
			var = var->next;
		if (var)
			modify(var, &splited);
		else
			add(env_lst, &splited);
	}
}

static void	modify(t_env *var, char ***splited)
{
	free(var->value);
	var->value = (*splited)[1];
	free((*splited)[0]);
	free((*splited));
	(*splited) = NULL;
}

static void	add(t_env **env_lst, char ***splited)
{
	expandenvlst(env_lst, (*splited));
	free(*splited);
	(*splited) = NULL;
}

static void freesplited(char ***splited)
{
	free((*splited)[0]);
	free((*splited)[1]);
	free((*splited));
	(*splited) = NULL;
}
