/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 14:21:15 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/27 10:36:55 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "signals.h"

#include <readline/readline.h>

int	g_exit_status;

void	interrupt(void)
{
	write(STDOUT_FILENO, "\n", sizeof(char));
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	exit_status(void)
{
	return (g_exit_status);
}

int	exit_status_set(int n)
{
	g_exit_status = n;
	return (n);
}
