/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:07:42 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/25 18:07:49 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_syntax_error(char *msg)
{
	ft_putstr_fd(SH_NAME ": ", 2);
	ft_putstr_fd(SYNTAX_ERR ": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
}
