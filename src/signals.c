/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 15:21:49 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 12:48:19 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>

void	sig_interupt(int signum)
{
	if (DEBUG)
		printf("received signal: %d\n", signum);
	if (signum == SIGINT)
	{
		interrupt();
		exit_status_set(1);
	}
}

void	sig_interupt_noredisplay(int signum)
{
	if (DEBUG)
		printf("received signal: %d\n", signum);
	if (signum == SIGINT)
	{
		exit_status_set(1);
		write(STDOUT_FILENO, "\n", sizeof(char));
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
