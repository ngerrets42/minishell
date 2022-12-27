/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/28 15:22:03 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/29 16:58:25 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "core.h"

# include <signal.h>

void	sig_interupt(int signum);
void	sig_interupt_noredisplay(int signum);

#endif
