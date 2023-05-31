/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 14:31:59 by ngerrets      #+#    #+#                 */
/*   Updated: 2023/01/05 15:28:36 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

struct s_str_func
{
	char		*str;
	t_builtin_f	func;
};

t_builtin_f	*builtin_get(const char *cmd)
{
	size_t						i;
	static struct s_str_func	array[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}
	};

	i = 0;
	while (array[i].str)
	{
		if (n_strlen(cmd) == n_strlen(array[i].str)
			&& n_strcmp(cmd, array[i].str) == 0)
			return (&(array[i].func));
		i++;
	}
	return (NULL);
}
