/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:31:48 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/08 16:12:04 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// if (!SHLVL || !isvalid(SHLVL) || SHLVL > 999) then SHLVL=1
//                          ^ this produces a warning when opening the shell
// if (SHLVL == 999) then SHLVL=""
// if (0 <= SHLVL <= 998) then SHLVL=SHLVL+1
// if (SHLVL < 0) then SHLVL=0
// DON'T PROTECT OVERFLOW!!

int			ft_strcmp(const char *s1, const char *s2);
int			ft_isdigit(int c);
int			ft_atoi(char *str);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2, char const *sep);
void		export(char **av, t_env **env_lst);
char		*ft_strdup(const char *s);
void		ft_putstr_fd(char const *s, int fd);
void		ft_putnbr_fd(int n, int fd);

static int	isvalid(t_env *shlvl);
static int	set_av1(char **av, t_env *shlvl);
static void	warning_case(int shelvl_value, char **av);

void	set_shlvl(t_env **env_lst)
{
	t_env	*shlvl;
	char	*av[3];

	shlvl = (*env_lst);
	while (shlvl && ft_strcmp(shlvl->key, "SHLVL"))
		shlvl = shlvl->next;
	if (!set_av1(av, shlvl))
		return ;
	av[2] = NULL;
	export(av, env_lst);
	free(av[1]);
}

static int	set_av1(char **av, t_env *shlvl)
{
	int		shelvl_value;
	char	*tmp;

	if (!isvalid(shlvl) || ft_atoi(shlvl->value) < 0)
		av[1] = ft_strdup("SHLVL=0");
	else
	{
		shelvl_value = ft_atoi(shlvl->value);
		if (shelvl_value == 999)
			av[1] = ft_strdup("SHLVL=");
		else if (shelvl_value > 999)
			warning_case(shelvl_value, av);
		else
		{
			tmp = ft_itoa(shelvl_value + 1);
			if (!tmp)
				return (0);
			av[1] = ft_strjoin("SHLVL", tmp, "=");
			free(tmp);
		}
	}
	if (!av[1])
		return (0);
	return (1);
}

static int	isvalid(t_env *shlvl)
{
	int	i;

	if (!shlvl || !shlvl->value)
		return (0);
	i = 0;
	while (shlvl->value[i] == ' ')
		i++;
	if (shlvl->value[i] == '-' || shlvl->value[i] == '+')
		i++;
	if (!ft_isdigit(shlvl->value[i]))
		return (0);
	while (ft_isdigit(shlvl->value[i]))
		i++;
	while (shlvl->value[i] == ' ')
		i++;
	if (shlvl->value[i] != '\0')
		return (0);
	return (1);
}

static void	warning_case(int shelvl_value, char **av)
{
	av[1] = ft_strdup("SHLVL=1");
	ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
	ft_putnbr_fd(shelvl_value + 1, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
}
