/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 14:43:22 by cstaats       #+#    #+#                 */
/*   Updated: 2022/12/05 14:35:44 by cstaats       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"

int	builtin_unset(int argc, char **argv, char ***env)
{
	char	*word;
	char	*p;
	size_t	index;

	write(STDOUT_FILENO, NULL, 0);
	if (argc == 1)
		return (0);
	argv++;
	while (*argv)
	{
		p = n_strfind(*argv, "=");
		if (!p)
			p = *argv + n_strlen(*argv);
		word = cpy_word(*argv, p);
		index = get_environment_index(*env, word);
		free(word);
		if ((*env)[index] != NULL)
			env_overwrite_var(env, index, "\0");
		argv++;
	}
	return (0);
}
	//	TODO: detect illegal characters
