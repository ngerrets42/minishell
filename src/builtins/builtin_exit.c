/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 14:20:18 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/29 14:42:16 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	is_numeric(const char *str)
{
	while (*str == '0')
		++str;
	if (n_strlen(str) >= 20)
		return (false);
	while (*str)
	{
		if (*str != '-' && (*str < '0' || *str > '9'))
			return (false);
		str++;
	}
	return (true);
}

int	builtin_exit(int argc, char **argv, char ***env)
{
	unsigned char	status;

	(void)env;
	status = exit_status();
	if (argc > 1)
	{
		if (!is_numeric(argv[1]))
		{
			perr("minishell: exit: ", argv[1], ": numeric argument required\n");
			return (exit_status_set(EXIT_STATUS_NUMERIC_ARG));
		}
		if (argc > 2)
		{
			perr("minishell: exit: too many arguments\n", NULL, NULL);
			return (exit_status_set(EXIT_FAILURE));
		}
		exit_status_set(ft_atoi(argv[1]));
	}
	return (EXIT_SUCCESS);
}
