/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.0.0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:52:22 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:52:03 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static t_list	*remove_node(t_list *env, char *arg)
{
	t_list	*hold;
	t_list	*head;
	t_list	*prev;

	head = env;
	hold = NULL;
	if (compare_keys(env, arg))
		return (remove_head(env));
	while (env)
	{
		if (compare_keys(env, arg))
		{
			hold = env;
			prev->next = env->next;
			free(hold->content);
			free(hold);
			break ;
		}
		else
			prev = env;
		env = env->next;
	}
	return (head);
}

static void	msg_error(char *arg)
{
	write (2, "minishell: ", 12);
	write (2, "unset: `", 9);
	write (2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
	g_glob.exit_status = 1;
}

static int	valid_argument(char *arg)
{
	int	j;

	j = ft_strlen(arg) - 1;
	if ((arg[0] < 65 || arg[0] > 90) && (arg[0] < 97
			|| arg[0] > 122) && arg[0] != 95)
		return (0);
	while (j > 0)
	{
		if (!alphaunder(arg[j]) && (!((arg[j] >= 48 && arg[j] <= 57))))
			return (0);
		j--;
	}
	return (1);
}

void	_unset(char **args)
{
	int		i;
	t_list	*tenv;

	i = 1;
	if (!args[i])
		return ;
	while (args[i])
	{
		tenv = g_glob.env;
		if (!valid_argument(args[i]))
			msg_error(args[i]);
		else
			g_glob.env = remove_node(tenv, args[i]);
		i++;
	}
	convert_to_array();
}
