/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:54:13 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:12:06 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	print_error2(char *shell_name, char *command, char *details,
		char *description)
{
	ft_putstr_fd(shell_name, STDERR_FILENO);
	if (shell_name && (command || details || description))
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	if (command && (details || description))
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(details, STDERR_FILENO);
	if (details && description)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(description, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
