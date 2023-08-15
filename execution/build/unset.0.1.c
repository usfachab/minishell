/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.0.1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:26:00 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:52:10 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	compare_keys(t_list *e, char *arg)
{
	char	*envkey;
	char	*equal;

	if (!e || !(e->content))
		return (0);
	envkey = ft_strdup(e->content);
	equal = ft_strchr(envkey, '=');
	if (equal)
		envkey[equal - envkey] = 0;
	if (!ft_strcmp(envkey, arg))
	{
		free(envkey);
		envkey = NULL;
		return (1);
	}
	free(envkey);
	envkey = NULL;
	return (0);
}

t_list	*remove_head(t_list *env)
{
	t_list	*hold;
	t_list	*head;

	hold = env;
	env = env->next;
	head = env;
	free(hold->content);
	free(hold);
	return (head);
}
