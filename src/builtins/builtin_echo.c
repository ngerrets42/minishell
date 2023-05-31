/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 14:43:22 by cstaats       #+#    #+#                 */
/*   Updated: 2023/01/05 15:26:03 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	writeandreturn(void)
{
	write (1, "\n", 1 * sizeof(char));
	return (0);
}

bool	is_flag(const char *arg)
{
	size_t	i;

	if (n_strlen(arg) < 2)
		return (false);
	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		++i;
	}
	return (true);
}

int	builtin_echo(int argc, char **argv, char ***envp)
{
	int		i;
	bool	newline;

	newline = true;
	(void)envp;
	i = 1;
	if (argc < 2)
		return (writeandreturn());
	while (i <= argc - 1 && is_flag(argv[i]))
	{
		newline = false;
		i++;
	}
	while (i <= argc - 1)
	{
		write(1, argv[i], n_strlen(argv[i]) * sizeof(char));
		if (i < argc - 1)
			write(1, " ", 1 * sizeof(char));
		i++;
	}
	if (newline != false)
		return (writeandreturn());
	return (0);
}
