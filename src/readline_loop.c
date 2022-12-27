/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline_loop.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 12:02:31 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/27 10:34:59 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "readline_loop.h"

static void	print_llist(t_llist *list, t_contentf print_func)
{
	t_llist	*curr;

	curr = list;
	while (curr && curr->content)
	{
		print_func(curr->content);
		curr = curr->next;
	}
}

void	debug_outp_tokens(const char *str, t_llist *tokenl)
{
	if (!DEBUG)
		return ;
	printf(CYELLOW"> STRING:\n>\t{%s}\n", str);
	if (tokenl)
	{
		printf("> TOKENIZER:\n");
		print_llist(tokenl, (t_contentf)token_print);
	}
	printf(CRESET);
}

void	debug_outp_commands(t_llist *cmdl)
{
	if (!DEBUG)
		return ;
	if (cmdl)
	{
		printf(CYELLOW"> COMMANDS:\n");
		print_llist(cmdl, (t_contentf)command_print);
		printf(CRESET);
	}
}

static void	implementation(char *str, char ***env)
{
	t_llist	*token_list;
	t_llist	*command_list;

	token_list = tokenize(str, env);
	debug_outp_tokens(str, token_list);
	command_list = commands_parse(token_list);
	debug_outp_commands(command_list);
	llist_clear(&token_list, (t_contentf)free);
	execute(command_list, llist_size(command_list), env);
	llist_clear(&command_list, (t_contentf)command_free);
}

int	readline_loop(char ***env)
{
	char	*str;
	t_llist	*str_list;

	str_list = NULL;
	while (true)
	{
		signal(SIGINT, sig_interupt);
		str = readline(PROMPT_STRING);
		signal(SIGINT, sig_interupt_noredisplay);
		if (!str)
			break ;
		if (n_strlen(str) == 0)
		{
			free(str);
			continue ;
		}
		add_history(str);
		llist_add_back(&str_list, llist_new(str));
		implementation(str, env);
	}
	llist_clear(&str_list, free);
	return (exit_status());
}
