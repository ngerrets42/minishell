/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 14:29:29 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 11:24:05 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "core.h"

typedef int	(*t_builtin_f)(int, char **, char ***);

t_builtin_f	*builtin_get(const char *cmd);

int			builtin_exit(int argc, char **argv, char ***env);
int			builtin_echo(int argc, char **argv, char ***env);
int			builtin_cd(int argc, char **argv, char ***env);
int			builtin_export(int argc, char **argv, char ***env);
int			builtin_unset(int argc, char **argv, char ***env);
int			builtin_env(int argc, char **argv, char ***envp);
int			builtin_pwd(int argc, char **argv, char ***env);

#endif
