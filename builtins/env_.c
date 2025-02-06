/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:52:52 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/06 10:23:19 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

char	**envlsttoenv(t_env *env_lst);
void	envlstclear(t_env **env_lst);
void	freestrarr(char ***arr);

void	env_(t_env *env_lst)
{
	int		i;
	char	**env;

	env = envlsttoenv(env_lst);
	if (!env)
		exit(EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	envlstclear(&env_lst);
	freestrarr(&env);
	exit(EXIT_SUCCESS);
}
