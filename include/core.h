/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   core.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 10:36:45 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/27 10:37:21 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "utils/llist.h"
# include "utils/n_alloc.h"
# include "utils/n_mem.h"
# include "utils/n_protect.h"
# include "utils/n_string.h"

# ifndef NOCOLORS
#  define CRED "\x1B[31m"
#  define CGREEN "\x1B[32m"
#  define CYELLOW "\x1B[33m"
#  define CBLUE "\x1B[34m"
#  define CMAGENTA "\x1B[35m"
#  define CCYAN "\x1B[36m"
#  define CWHITE "\x1B[37m"
#  define CRESET "\x1B[0m"
#  define PROMPT_STRING "minishell$ "
# else
#  define CRED ""
#  define CGREEN ""
#  define CYELLOW ""
#  define CBLUE ""
#  define CMAGENTA ""
#  define CCYAN ""
#  define CWHITE ""
#  define CRESET ""
#  define PROMPT_STRING "minishell$ "
# endif

# define SHELL_LEVEL_VAR "SHLVL"

# define EXIT_STATUS_CMD_NOT_FOUND 127

extern int	g_exit_status;

char	*cpy_word(char *pstart, char *pend);
void	add_str_to_arr(char ***argv, char *str);
int		exit_status(void);
int		exit_status_set(int n);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
void	interrupt(void);
int		perr(const char *str1, const char *str2, const char *str3);

#endif
