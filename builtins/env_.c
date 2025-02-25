/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:52:52 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/25 12:55:05 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executing.h"

void	env_(t_env *env_lst, t_exec *x)
{
	int		i;
	char	**env;

	if (!env_lst)
		return ;
	env = envlsttoenv(env_lst);
	if (!env)
	{
		x->status = 1;
		return ;
	}
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	freestrarr(&env);
	x->status = 0;
}
