/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:28:44 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/08 15:24:33 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		internal_error_msg("", ENOMEM);
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}

void	lexer_advence(t_lexer *lexer)
{
	if (lexer->c && lexer->i < ft_strlen(lexer->content))
	{
		lexer->i += 1;
		lexer->c = lexer->content[lexer->i];
	}
}

int	identifier(t_lexer *lexer)
{
	if (lexer->c == '|' || lexer->c == '<' || lexer->c == '>'
		|| lexer->c == '\0' || lexer->c == '\n')
		return (1);
	return (0);
}

char	*lexer_collect_string(t_lexer *lexer)
{
	char	*tmp;
	char	*string;
	int		len;

	string = NULL;
	lexer_skip_white_space(lexer);
	if (!lexer->c)
		return (NULL);
	len = 0;
	while (!identifier(lexer))
	{
		tmp = malloc(len + 2);
		if (string != NULL)
		{
			ft_memmove(tmp, string, len);
			free(string);
			string = NULL;
		}
		string = tmp;
		string[len] = lexer->c;
		string[len + 1] = '\0';
		len++;
		lexer_advence(lexer);
	}
	return (string);
}

char	*lexer_collect_file_name(t_lexer *lexer)
{
	char	*tmp;
	char	*string;
	int		len;

	string = NULL;
	lexer_skip_white_space(lexer);
	len = 0;
	while (!identifier(lexer) && lexer->c != 32)
	{
		tmp = malloc(len + 2);
		if (!tmp)
			internal_error_msg("", ENOMEM);
		if (string != NULL)
		{
			ft_memmove(tmp, string, len);
			free(string);
		}
		string = tmp;
		string[len] = lexer->c;
		string[len + 1] = '\0';
		len++;
		lexer_advence(lexer);
	}
	return (string);
}
