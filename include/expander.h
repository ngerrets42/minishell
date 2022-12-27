/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 12:06:26 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/01 13:02:19 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "core.h"

char	*get_environment_var(char **env, const char *var_name);
size_t	get_environment_index(char **env, const char *var_name);
char	*get_path(char *cmd, char **env);

bool	expand_argument(char **arg, char **env);

//	expander_utils.c
char	*n_strhaschar_set(const char *str, char *set);
void	env_add_var(char ***env, char *arg);
void	env_overwrite_var(char ***env, size_t index, char *arg);
char	**env_set(char ***env, const char *var, const char *value);

#endif	//	EXPANDER_H
