/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:33:57 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:44:12 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_BONUS_H
# define BUILTINS_BONUS_H

# include "parsing_bonus.h"

void	cd(char **av, t_env **env_lst, t_exec *x);
void	echo(char **av, t_exec *x);
int		gohome(t_env **env_lst);
void	set_env(t_env **env_lst, t_exec *x);
void	_export(char **av, t_env **env_lst, t_exec *x);
void	unset(char **av, t_env **env_lst, t_exec *x);
void	env_(t_env *env_lst, t_exec *x);
void	exit_(char **av, bool print, t_exec *x);
void	pexport(t_env *env_lst);
void	pwd(t_exec *x);

#endif
