/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 22:33:07 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/11 19:16:58 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lib.h"

void	restofrest(t_parser_var *var)
{
	free(var->command);
	free(var->file);
	free(var->lexer);
	free(var->token);
	free(var->data);
	if (var->pid)
		free(var->pid);
}

void	free_close(t_data *data)
{
	t_file	*file_next;

	if (data->last_hdc > 2)
		close(data->last_hdc);
	if (data->in > 2)
		close(data->in);
	if (data->out > 2)
		close(data->out);
	if (data->prev > 2)
		close(data->prev);
	while (data && data->file)
	{
		file_next = data->file->next;
		free(data->file->file_name);
		free(data->file);
		data->file = file_next;
	}
}

void	reset(t_parser_var *var)
{
	int		i;
	t_data	*data_next;

	if (var)
	{
		while (var->data)
		{
			i = -1;
			while (var->data->cmd_args && var->data->cmd_args[++i])
				free(var->data->cmd_args[i]);
			free_close(var->data);
			data_next = var->data->next;
			free(var->data->cmd_args);
			free(var->data);
			var->data = data_next;
		}
		restofrest(var);
	}
}
