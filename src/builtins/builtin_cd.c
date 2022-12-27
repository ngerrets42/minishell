/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/01 12:12:53 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 14:25:23 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"

void	set_newpwd(char ***env)
{
	char	*newpath;

	newpath = getcwd(NULL, 0);
	if (!newpath)
		newpath = env[1][0];
	if (get_environment_var(*env, "PWD"))
		env_set(env, "PWD", newpath);
	free(env[1][0]);
	env[1][0] = newpath;
}

void	set_oldpwd(char ***env)
{
	char	*oldpath;

	oldpath = getcwd(NULL, 0);
	if (!oldpath)
		oldpath = env[1][1];
	if (get_environment_var(*env, "OLDPWD"))
		env_set(env, "OLDPWD", oldpath);
	free(env[1][1]);
	env[1][1] = oldpath;
}

int	builtin_cd(int argc, char **argv, char ***env)
{
	char	*dir;

	set_oldpwd(env);
	dir = get_environment_var(*env, "HOME");
	if (argc > 1)
		dir = argv[1];
	if (!dir)
		return (EXIT_FAILURE + 0
			* perr("minishell: cd: HOME directory not found\n", NULL, NULL));
	if (chdir(dir) != 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	set_newpwd(env);
	return (EXIT_SUCCESS);
}
