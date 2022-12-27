/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 15:21:49 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/29 16:58:39 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>

void	sig_interupt(int signum)
{
	if (DEBUG)
		printf("received signal: %d\n", signum);
	if (signum == SIGINT)
		interrupt();
}

void	sig_interupt_noredisplay(int signum)
{
	if (DEBUG)
		printf("received signal: %d\n", signum);
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", sizeof(char));
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
