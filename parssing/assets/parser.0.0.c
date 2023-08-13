/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.0.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:48:06 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 19:04:11 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

static t_parser_var	*init_var(char *input, t_parser_var	*var)
{
	var->pid = NULL;
	var->data = NULL;
	var->lexer = init_lexer(input);
	var->token = lexer_get_next_token(var->lexer);
	var->file = NULL;
	var->command = ft_strdup("");
	var->_command = NULL;
	return (var);
}

void	expand_in_command(t_parser_var *var)
{
	char	*exp;

	exp = NULL;
	find_unprintable_and_replace_with_char(var->token->value);
	exp = expand(var->token->value, g_glob.envp, 0);
	if (exp && exp != var->token->value)
	{
		free(var->token->value);
		var->token->value = ft_strdup(exp);
		free(exp);
	}
	find_char_and_replace_with_unprintable(var->token->value);
}

void	collect_command(t_parser_var *var)
{
	if (var->token->value && var->token->e_type == 0)
	{
		if (ft_strchr(var->token->value, '$'))
			expand_in_command(var);
		var->command = _join(var->command, var->token->value);
		free(var->token->value);
	}
}

void	create_node(t_parser_var *var)
{
	if (var->token->e_type == 1 ||!var->lexer->c)
	{
		if (var->lexer->c)
			free(var->token->value);
		find_char_and_replace_with_unprintable(var->command);
		var->_command = split(var->command, " \t");
		find_unprintable_replace_space(var->_command);
		ft_lstadd_back_node(&(var->data),
			ft_lstnew_node(var->_command, var->file));
		free(var->command);
		var->command = ft_strdup("");
		var->file = NULL;
		g_glob.exit_status = 0;
	}
}

t_parser_var	*parser(char *input, t_parser_var	*var)
{
	find_char_and_replace_with_unprintable(input);
	var = init_var(input, var);
	while (var->token)
	{
		collect_command(var);
		save_file(var);
		save_heredoc(var);
		create_node(var);
		free(var->token);
		var->token = lexer_get_next_token(var->lexer);
	}
	return (var);
}
