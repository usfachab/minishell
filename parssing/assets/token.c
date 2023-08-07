/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 23:48:29 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/02 17:59:48 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

t_token	*lexer_collect_identifier(t_lexer *lexer)
{
	if (lexer->c == '<')
	{
		lexer_advence(lexer);
		if (lexer->c == '<')
		{
			lexer_advence(lexer);
			return (init_token(TOKEN_HDC, lexer_collect_file_name(lexer)));
		}
		return (init_token(TOKEN_INFILE, lexer_collect_file_name(lexer)));
	}
	else if (lexer->c == '>')
	{
		lexer_advence(lexer);
		if (lexer->c == '>')
		{
			lexer_advence(lexer);
			return (init_token(TOKEN_APPAND, lexer_collect_file_name(lexer)));
		}
		return (init_token(TOKEN_OUTFILE, lexer_collect_file_name(lexer)));
	}
	return (NULL);
}

t_token	*lexer_advence_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advence(lexer);
	return (token);
}

char	*lexer_char_as_string(t_lexer *lexer)
{
	char	*string;

	string = malloc(2 * sizeof(char));
	if (!string)
	{
		g_glob.exit_status = errno;
		exit(errno);
	}
	string[0] = lexer->c;
	string[1] = '\0';
	return (string);
}

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(struct TOKEN_STRUCT));
	if (!token)
	{
		g_glob.exit_status = errno;
		exit(errno);
	}
	token->e_type = type;
	token->value = value;
	return (token);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c && lexer->i < strlen(lexer->content))
	{
		lexer_skip_white_space(lexer);
		if (lexer->c == '<' || lexer->c == '>')
			return (lexer_collect_identifier(lexer));
		if (lexer->c == '|')
			return (lexer_advence_with_token(lexer, init_token(TOKEN_PIPE,
						lexer_char_as_string(lexer))));
		else
			return (init_token(TOKEN_STRING, lexer_collect_string(lexer)));
	}
	return (NULL);
}
