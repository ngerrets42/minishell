/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:11:21 by cstaats       #+#    #+#                 */
/*   Updated: 2022/12/27 10:30:37 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(int argc, char **argv, char ***envp)
{
	int		i;
	size_t	len;

	(void)argv;
	(void)argc;
	i = 0;
	if (**envp == NULL)
	{
		write (1, "\n", 1);
		return (0);
	}
	while ((*envp)[i] != NULL)
	{
		len = n_strlen((*envp)[i]);
		if (len > 0)
		{
			write(1, (*envp)[i], len * sizeof(char));
			write(1, "\n", 1 * sizeof(char));
		}
		i++;
	}
	return (0);
}
