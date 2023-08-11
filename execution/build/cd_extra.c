/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:26:04 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/11 16:59:29 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	ft_store_pwd(t_parser_var *var)
{
	t_list	*tmp;

	tmp = var->env;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (!ft_strncmp("PWD=", tmp->content, 4)
			|| !ft_strncmp("PWD", tmp->content, 4))
		{
			free(tmp->content);
			tmp->content = NULL;
			tmp->content = ft_strjoin("PWD=", g_glob.pwd);
		}
		else if (!ft_strncmp("OLDPWD=", tmp->content, 7)
			|| !ft_strncmp("OLDPWD", tmp->content, 7))
		{
			free(tmp->content);
			tmp->content = NULL;
			tmp->content = ft_strjoin("OLDPWD=", g_glob.oldpwd);
		}
		tmp = tmp->next;
	}
	convert_to_array(var);
}
