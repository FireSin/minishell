/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:21 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:22 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_mes_with_exit(char *err_mes, t_data *data)
{
	printf("%s", err_mes);
	if (data->comm)
		delcommand(&data->comm);
	if (data->env)
		delenv(&data->env);
	if (data->instr)
		free(data->instr);
	exit(errno);
}

void	freedata(t_data *data)
{
	delcommand(&data->comm);
	if (data->instr)
	{
		free(data->instr);
		data->instr = NULL;
	}
}

void	exit_from_minishell(void)
{
	printf("Fail from 'exit_from_minishell'\n");
	exit(1);
	return ;
}

int	get_count_comm(t_comm *data)
{
	int	count;

	count = 0;
	while (data)
	{
		count++;
		data = data->next;
	}
	return (count);
}

int	kill_childs(t_comm *data)
{
	while (data->prev)
		data = data->prev;
	while (data)
	{
		if (kill(data->pid, SIGKILL))
			return (1);
		data = data->next;
	}
	return (0);
}
