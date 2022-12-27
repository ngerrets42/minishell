/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 09:34:33 by cstaats       #+#    #+#                 */
/*   Updated: 2022/12/07 14:25:35 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_pwd(int argc, char **argv, char ***env)
{
	char	cwd[1024];

	(void)argc;
	(void)argv;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		printf("%s\n", env[1][0]);
	return (0);
}
