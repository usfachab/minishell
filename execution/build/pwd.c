/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:51:34 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/02 21:56:27 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	_pwd(t_list *env)
{
	t_list	*temp;
	char	*str;

	temp = env;
	str = getcwd(NULL, 0);
	if (!str)
	{
		while (temp)
		{
			if (ft_strnstr(temp->content, "PWD=", 4))
			{
				printf("%s\n", temp->content + 4);
				free(str);
				return ;
			}
			temp = temp->next;
		}
		printf("%s\n", g_glob.pwd_helper);
		free(str);
	}
	else
	{
		printf("%s\n", str);
		free(str);
	}
}
