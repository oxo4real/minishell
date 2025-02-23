/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:52:52 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/23 18:43:12 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_(t_env *env_lst)
{
	int		i;
	char	**env;

	if (!env_lst)
		return ;
	env = envlsttoenv(env_lst);
	if (!env)
		exit(EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	// envlstclear(&env_lst);
	freestrarr(&env);
	// exit(EXIT_SUCCESS);
}
