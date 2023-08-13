/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.0.1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:58 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 19:02:49 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

void	expand_in_file(t_parser_var *var)
{
	char	*exp;

	exp = NULL;
	find_unprintable_and_replace_with_char(var->token->value);
	exp = expand(var->token->value, g_glob.envp, 0);
	if (exp && (!exp[0] || variable_contain_white_space(exp)))
	{
		g_glob.ambiguous = -1;
		free(exp);
		exp = NULL;
	}
	else if (exp && exp != var->token->value)
	{
		free(var->token->value);
		var->token->value = ft_strdup(exp);
		free(exp);
	}
	find_char_and_replace_with_unprintable(var->token->value);
}

void	save_file(t_parser_var	*var)
{
	if (var->token->value && (var->token->e_type == 2
			|| var->token->e_type == 3 || var->token->e_type == 4))
	{
		if (ft_strchr(var->token->value, '$'))
		{
			expand_in_file(var);
			if (g_glob.ambiguous == -1)
			{
				var->token->e_type = -1;
				g_glob.ambiguous = 0;
			}
		}
		if (ft_strchr(var->token->value, '\'')
			|| ft_strchr(var->token->value, '\"'))
			var->token->value = remove_quote(var->token->value);
		find_unprintable_and_replace_with_char(var->token->value);
		ft_lstadd_back_subnode(&(var->file),
			ft_lstnew_subnode(var->token->value, var->token->e_type));
	}
}

void	save_heredoc(t_parser_var *var)
{
	if (var->token->e_type == 5)
	{
		if (ft_strchr(var->token->value, '\'')
			|| ft_strchr(var->token->value, '\"'))
		{
			var->token->value = remove_quote(var->token->value);
			var->token->e_type = 6;
		}
		find_unprintable_and_replace_with_char(var->token->value);
		ft_lstadd_back_subnode(&(var->file),
			ft_lstnew_subnode(var->token->value, var->token->e_type));
	}
}
