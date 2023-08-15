/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:49:47 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:50:34 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static void	print_result(char **cmd, int stat_of_first_arg)
{
	char	c;

	if (!stat_of_first_arg)
	{
		if (!(*(cmd + 1)))
			c = '\0';
		else
			c = ' ';
		printf("%s%c", *cmd, c);
	}
	else
	{
		if (!(*(cmd + 1)))
			c = '\n';
		else
			c = ' ';
		printf("%s%c", *cmd, c);
	}
}

static int	check_the_first_argument(char *arg)
{
	if (arg[0] == '-')
	{
		arg = arg + 1;
		if (!(*arg))
			return (1);
	}
	else
		return (1);
	while (arg && *arg)
	{
		if (*arg != 'n')
			return (1);
		arg++;
	}
	return (0);
}

void	_echo(char **cmd)
{
	int	stat_of_first_arg;

	stat_of_first_arg = 0;
	if (!(*(cmd + 1)))
	{
		printf("\n");
		return ;
	}
	else
		cmd = cmd + 1;
	stat_of_first_arg = check_the_first_argument(*cmd);
	while (*(*cmd) == '-' && !check_the_first_argument(*cmd))
	{
		if (!(*(cmd + 1)))
		{
			printf("%c", '\0');
			return ;
		}
		cmd++;
	}
	while (cmd && *cmd)
	{
		print_result(cmd, stat_of_first_arg);
		cmd++;
	}
}
