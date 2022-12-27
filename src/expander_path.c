/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 13:34:33 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/27 10:34:59 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//	Get the contents of environment variable var from the environment env.
//	Returns the pointer to the variable string (or NULL if not found)
char	*get_environment_var(char **env, const char *var_name)
{
	size_t	i;
	char	*eq_pos;

	i = 0;
	if (var_name[0] == '?')
		return (n_protect(ft_itoa(exit_status())));
	while (env[i] != NULL)
	{
		eq_pos = n_strfind(env[i], "=");
		if (!eq_pos)
			eq_pos = env[i] + n_strlen(env[i]);
		if ((size_t)(eq_pos - env[i]) == n_strlen(var_name)
			&& n_strcmp(env[i], var_name) == 0)
			return (env[i] + n_strlen(var_name) + 1);
		i++;
	}
	return (NULL);
}

size_t	get_environment_index(char **env, const char *var_name)
{
	size_t	i;
	char	*eq_pos;

	i = 0;
	while (env[i] != NULL)
	{
		eq_pos = n_strfind(env[i], "=");
		if (!eq_pos)
			eq_pos = env[i] + n_strlen(env[i]);
		if ((size_t)(eq_pos - env[i]) == n_strlen(var_name)
			&& n_strcmp(env[i], var_name) == 0)
			return (i);
		i++;
	}
	return (i);
}

static char	**set_join(char *cmd)
{
	static char	*join[4];

	join[0] = NULL;
	join[1] = "/";
	join[2] = cmd;
	join[3] = NULL;
	return (join);
}

// NOTE: var shouldn't be freed after getting it from the environment.
//		the pointer is reused in the loop however, and needs to be freed there.
char	*get_path(char *cmd, char **env)
{
	char	**join;
	char	**directories;
	char	*var;
	size_t	i;

	var = get_environment_var(env, "PATH");
	if (!var)
		return (NULL);
	directories = n_protect(n_split(var, ":"));
	i = 0;
	join = set_join(cmd);
	while (directories[i])
	{
		join[0] = directories[i];
		var = n_protect(n_strarr_join(join));
		if (access(var, F_OK | X_OK) == 0)
		{
			n_strarr_free(directories);
			return (var);
		}
		free(var);
		i++;
	}
	n_strarr_free(directories);
	return (NULL);
}
