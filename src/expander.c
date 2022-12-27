/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 12:03:57 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/27 10:20:24 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//	expands a given command to it's full path
//	NOTE: cmd is a reference to the string
void	expand_to_path(char **cmd, char **env)
{
	char	*path;

	path = get_path(*cmd, env);
	if (!path)
		path = n_zalloc(1 * sizeof(char));
	free(*cmd);
	*cmd = path;
}

char	*str_inserted(char *str, char *startp, char *endp, char *str_insert)
{
	char	*result;
	size_t	i;
	size_t	j;

	result = n_protect(n_zalloc((startp - str)
				+ (n_strlen_p(str_insert) * sizeof(char))
				+ (n_strlen(endp) * sizeof(char)) + sizeof(char)));
	i = 0;
	j = 0;
	while (str + j < startp)
		result[i++] = str[j++];
	j = 0;
	while (str_insert && j < n_strlen(str_insert))
		result[i++] = str_insert[j++];
	j = 0;
	while (j < n_strlen(endp))
		result[i++] = endp[j++];
	return (result);
}

static char	*get_pend(char *pstart)
{
	char	*pend;

	if (pstart[1] == '?')
		pend = pstart + 2;
	else
		pend = n_strhaschar_set(pstart + 1, "$ =\t");
	if (!pend)
		pend = pstart + n_strlen(pstart);
	return (pend);
}

//	arg is a reference to the argument string
//	returns true when it finds a $, false otherwise
bool	expand_argument(char **arg, char **env)
{
	char	*pstart;
	char	*pend;
	char	*var;
	char	*env_var;

	pstart = *arg;
	while (*arg)
	{
		pstart = n_strfind(pstart, "$");
		if (!pstart)
			return (false);
		pend = get_pend(pstart);
		var = cpy_word(pstart + 1, pend);
		env_var = get_environment_var(env, var);
		free(var);
		var = str_inserted(*arg, pstart, pend, env_var);
		pend = n_strlen_p(env_var) + (pstart - *(size_t *)arg);
		if (pstart[1] == '?')
			free(env_var);
		pstart = pend;
		free(*arg);
		*arg = var;
		pstart = *arg + (size_t)pstart;
	}
	return (true);
}
