/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.0.1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:26:00 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/11 17:25:20 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	compare_keys(t_list *e, char *arg)
{
	int		size;
	char	*envkey;
	char	*equal;

	if (!e || !(e->content))
		return (0);
	envkey = ft_strdup(e->content);
	equal = ft_strchr(envkey, '=');
	if (equal)
		envkey[equal - envkey] = 0;
	size = ft_strlen(envkey);
	free(envkey);
	if (!ft_strncmp(e->content, arg, size))
		return (1);
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