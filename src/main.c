/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 15:09:20 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 11:14:10 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	The general structure of minishell:
**
**	READING ---> TOKENIZING ---> COMMANDS ---> EXECUTION
**
**	READING:
**		Read input through the use of readline() and handling history.
**	
**	TOKENIZING:
**		Process the read input into a number of basic tokens and substrings.
**		Every token represents a diffent way of how to handle the read input.
**	
**	COMMANDS:
**		Convert the tokens into a set of command structs in order to sanitize
**		input and trivialize execution.
**	
**	EXECUTION:
**		Execute the instructions in order. This includes the build ins.
**
*/

#include "signals.h"
#include "readline_loop.h"

static void	remove_term_controlchars(void)
{
	struct termios	ctl;

	tcgetattr(STDIN_FILENO, &ctl);
	ctl.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ctl);
}

static char	*shell_level_build(char *shlvl)
{
	char	*ret;
	char	*p;
	int		n;

	n = ft_atoi(shlvl) + 1;
	p = n_protect(ft_itoa(n));
	ret = n_protect(n_zalloc(sizeof(char)
				* (n_strlen(SHELL_LEVEL_VAR) + n_strlen(p) + 2)));
	n_memcpy(ret, SHELL_LEVEL_VAR,
		sizeof(char) * n_strlen(SHELL_LEVEL_VAR));
	n_memcpy(ret + n_strlen(SHELL_LEVEL_VAR), "=", sizeof(char));
	n_memcpy(ret + n_strlen(SHELL_LEVEL_VAR) + 1, p,
		sizeof(char) * (n_strlen(p) + 1));
	free(p);
	return (ret);
}

static void	sigq(int c)
{
	(void)c;
	rl_redisplay();
}

static void	set_greater_env(char ***env)
{
	char	*pwd;
	char	*oldpwd;
	char	*tmp;

	env[1] = n_protect(n_zalloc(sizeof(char *) * 2));
	tmp = get_environment_var(*env, "PWD");
	pwd = n_protect(n_memdup(tmp, sizeof(char) * (n_strlen(tmp) + 1)));
	tmp = get_environment_var(*env, "OLDPWD");
	if (tmp)
		oldpwd = n_protect(n_memdup(tmp, sizeof(char) * (n_strlen(tmp) + 1)));
	env[1][0] = pwd;
	if (tmp)
		env[1][1] = oldpwd;
}

int	main(int argc, char **argv, char **env)
{
	char	**env_cpy;
	char	***greater_env;
	char	*shlvl;

	(void)argc;
	(void)argv;
	perr(CRED, NULL, NULL);
	remove_term_controlchars();
	signal(SIGQUIT, sigq);
	greater_env = n_protect(n_zalloc(sizeof(void *) * 2));
	env_cpy = n_protect(n_strarr_dup(env));
	greater_env[0] = env_cpy;
	set_greater_env(greater_env);
	shlvl = get_environment_var(env_cpy, SHELL_LEVEL_VAR);
	if (!shlvl || n_strlen(shlvl) == 0)
		env_add_var(&env_cpy, SHELL_LEVEL_VAR"=1");
	else
	{
		shlvl = shell_level_build(shlvl);
		env_overwrite_var(greater_env,
			get_environment_index(env_cpy, SHELL_LEVEL_VAR), shlvl);
		free(shlvl);
	}
	return (readline_loop(greater_env));
}
