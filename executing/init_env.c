/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:28 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/25 19:45:45 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executing.h"
#include "parsing.h"

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
