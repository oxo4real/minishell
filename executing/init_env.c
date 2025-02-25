/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:28 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/25 18:35:29 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executing.h"

void	init_env(t_env **env_lst)
{
	char	*av[3];

	av[2] = NULL;
	set_shlvl(env_lst);
	av[1] = ".";
	cd(av, env_lst);
	av[1] = "OLDPWD";
	unset(av, env_lst);
	_export(av, env_lst);
}
