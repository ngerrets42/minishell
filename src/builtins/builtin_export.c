/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 14:43:22 by cstaats       #+#    #+#                 */
/*   Updated: 2022/12/27 14:59:05 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"

static void	put(char *str)
{
	char	*p;

	if (n_strlen(str) == 0)
		return ;
	p = n_strfind(str, "=");
	if (!p)
	{
		printf("declare -x %s\n", str);
		return ;
	}
	p++;
	printf("declare -x %.*s=\"%s\"\n", (int)((p - str - 1) / sizeof(char)),
		str, p);
}

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	print_env_sorted(char ***env)
{
	char	**env_s;
	size_t	i;
	size_t	j;

	env_s = n_protect(n_strarr_dup(*env));
	i = 0;
	while (i < n_strarr_size(env_s))
	{
		j = 0;
		while (j < n_strarr_size(env_s))
		{
			if (n_strcmp(env_s[i], env_s[j]) < 0 || (n_strlen(env_s[i])
					< n_strlen(env_s[j]) && n_strcmp(env_s[i], env_s[j]) == 0))
				swap(&env_s[i], &env_s[j]);
			j++;
		}
		i++;
	}
	n_strarr_exec(env_s, put);
	n_strarr_free(env_s);
	return (0);
}

static bool	valid_export(const char *str, int *code)
{
	size_t	i;

	i = 0;
	if (str[0] == '=')
	{
		perr("minishell: export:`", str, "\' not a valid identifier\n");
		*code = 1;
		return (false);
	}
	if (n_strhaschar("0123456789", str[0]))
		++i;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
		{
			perr("minishell: export:`", str, "\' not a valid identifier\n");
			*code = 1;
			return (false);
		}
		++i;
	}
	return (true);
}

int	builtin_export(int argc, char **argv, char ***env)
{
	char	*word;
	char	*p;
	size_t	index;

	if (argc == 1)
		return (print_env_sorted(env));
	argc = 0 * (size_t)(++argv);
	while (*argv)
	{
		if (valid_export(*argv, &argc))
		{
			p = n_strfind(*argv, "=");
			if (!p)
				p = *argv + n_strlen(*argv);
			word = cpy_word(*argv, p);
			index = get_environment_index(*env, word);
			free(word);
			if ((*env)[index] != NULL && n_strfind(*argv, "="))
				env_overwrite_var(env, index, *argv);
			else if ((*env)[index] == NULL)
				env_add_var(env, *argv);
		}
		argv++;
	}
	return (exit_status_set(argc));
}
