/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:26:04 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/09 18:27:41 by selrhair         ###   ########.fr       */
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
		if (ft_strnstr(tmp->content, "PWD=", 4))
		{
			free(tmp->content);
			free(tmp->next->content);
			tmp->content = ft_strjoin("PWD=", g_glob.pwd);
			tmp->next->content = ft_strjoin("OLDPWD=", g_glob.oldpwd);
		}
		tmp = tmp->next;
	}
}
