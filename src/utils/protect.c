/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 17:24:21 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 14:05:57 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/n_protect.h"

#include <stdlib.h>
#include <stdio.h>

void	n_error_and_exit(void)
{
	perror("minishell");
	exit(EXIT_FAILURE);
}

t_protect_f	n_protect_setf(t_protect_f func)
{
	static t_protect_f	protf = n_error_and_exit;

	if (func != NULL)
		protf = func;
	return (protf);
}

void	*n_protect(void *ptr)
{
	if (!ptr)
		n_protect_setf(NULL)();
	return (ptr);
}
