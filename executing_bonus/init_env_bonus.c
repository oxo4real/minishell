/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:28 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:11:39 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"
#include "executing_bonus.h"
#include "parsing_bonus.h"

void	init_env(t_env **env_lst, t_exec *x)
{
	char	*av[3];

	av[2] = NULL;
	set_shlvl(env_lst, x);
	av[1] = ".";
	cd(av, env_lst, x);
	av[1] = "OLDPWD";
	unset(av, env_lst, x);
	_export(av, env_lst, x);
}
