/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 12:55:57 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 12:45:43 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//	Find and return a pointer to the first found instance of c in a set(or NULL)
char	*n_strhaschar_set(const char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (n_strhaschar(set, str[i]))
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

void	env_add_var(char ***env, char *arg)
{
	size_t	i;

	i = 0;
	while ((*env)[i])
	{
		if (n_strlen((*env)[i]) == 0)
		{
			env_overwrite_var(env, i, arg);
			return ;
		}
		i++;
	}
	add_str_to_arr(env, n_protect(n_memdup(arg, sizeof(char)
				* (n_strlen(arg) + 1))));
}

void	env_overwrite_var(char ***env, size_t index, char *arg)
{
	char	**pos;

	pos = (*env) + index;
	free(*pos);
	*pos = n_protect(n_memdup(arg, sizeof(char) * (n_strlen(arg) + 1)));
}

char	**env_set(char ***env, const char *var, const char *value)
{
	size_t	index;
	char	*str;

	str = n_protect(n_zalloc(sizeof(char)
				* (n_strlen(var) + n_strlen(value) + 2)));
	n_memcpy(str, var, sizeof(char) * n_strlen(var));
	n_memcpy(str + n_strlen(var), "=", sizeof(char));
	n_memcpy(str + n_strlen(var) + 1, value, sizeof(char) * n_strlen(value));
	index = get_environment_index(*env, var);
	if ((*env)[index] != NULL)
		env_overwrite_var(env, index, str);
	else
		env_add_var(env, str);
	free(str);
	return (*env + index);
}
