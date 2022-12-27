/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 14:20:18 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/27 10:34:03 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	is_numeric(const char *str)
{
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
		if (argc > 2)
		{
			perr("minishell: exit: too many arguments\n", NULL, NULL);
			exit(EXIT_FAILURE);
		}
		if (!is_numeric(argv[1]))
		{
			printf("exit\n");
			perr("minishell: exit: ", argv[1], ": numeric argument required\n");
			exit(EXIT_FAILURE);
		}
		status = ft_atoi(argv[1]);
	}
	printf("exit\n");
	exit(status);
	return (status);
}
