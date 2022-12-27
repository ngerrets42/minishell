/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline_loop.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 12:02:41 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 12:05:57 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_LOOP_H

# include "core.h"
# include "tokens.h"
# include "expander.h"
# include "executor.h"
# include "signals.h"
# include "command.h"

int	readline_loop(char ***env);

#endif	//	READLINE_LOOP_H
