/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __syntax.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:51:16 by yachaab           #+#    #+#             */
/*   Updated: 2023/07/30 19:57:47 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

void	*unclosed_quote(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			i++;
			while (input[i] != quote || !input[i])
			{
				if (input[i] == quote)
					break ;
				else if (!input[i])
				{
					printf("Syntax error near to %c\n", quote);
					return (NULL);
				}
				i++;
			}
		}
		i++;
	}
	return ("OK");
}

int	redirection(char *input)
{
	if (input && *input == '>')
		input++;
	else if (input && *input == '<')
		input++;
	else
		return (0);
	return (1);
}

int	inredirect(char *input)
{
	if (input && *input == '<')
	{
		input++;
		if (*input == '<')
			input++;
		input = skip_white_space(input);
		if (!(*input) || *input == '|' || (*input == '<' || *input == '>'))
		{
			printf("syntax error near to token `newline\'\n");
			return (0);
		}
	}
	return (1);
}

int	outredirect(char *input)
{
	if (input && *input == '>')
	{
		input++;
		if (*input == '>')
			input++;
		input = skip_white_space(input);
		if (!(*input) || *input == '|'
			|| *input == '\n' || (*input == '<' || *input == '>'))
		{
			printf("syntax error near to token <\n");
			return (0);
		}
	}
	return (1);
}

void	*redirection_error(char *input)
{
	while (input && *input)
	{
		if (!inredirect(input))
			return (NULL);
		if (!outredirect(input))
			return (NULL);
		input++;
	}
	return ("OK");
}
