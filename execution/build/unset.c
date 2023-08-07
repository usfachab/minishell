/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:52:22 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/03 17:46:43 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	ft_detangle(int i, t_parser_var *var)
{
	t_list	*tmp;
	t_list	*save;

	save = var->env;
	if (i == 0)
	{
		tmp = var->env;
		var->env = var->env->next;
		return ;
	}
	while (i-- > 1)
		var->env = var->env->next;
	tmp = var->env->next;
	var->env->next = var->env->next->next;
	tmp->next = NULL;
	var->env = save;
}

void	ft_unset(t_parser_var *var)
{
	int		i;
	int		j;
	t_list	*tmp;

	if (!var->data->cmd_args[1])
		return ;
	j = 1;
	while (var->data->cmd_args[j])
	{
		tmp = var->env;
		i = 0;
		while (tmp)
		{
			if (ft_strnstr(tmp->content, var->data->cmd_args[j],
					ft_strlen(var->data->cmd_args[j])))
				ft_detangle(i, var);
			i++;
			tmp = tmp->next;
		}
		j++;
	}
	convert_to_array(var);
}
