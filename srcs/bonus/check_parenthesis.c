/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:04:58 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 20:27:28 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_process_and_set_next_ptr(t_data *data)
{
	if (waitpid(data->comm->prnt, &data->comm->status, 0) == -1)
		ft_putstr_fd("Error waitpid\n", 2);
	if (WIFEXITED(data->comm->status))
		errno = WEXITSTATUS(data->comm->status);
	set_next_ptr_data_and_free_path(data);
	return (1);
}

int	parenthesis_logic(int c, t_data *data, t_comm *tmp_dt)
{
	char	*new_instr;

	check_oper(data);
	data->comm->prnt = fork();
	if (data->comm->prnt == 0)
	{
		if (handle_oper(data, c))
			return (1);
		new_instr = ft_strdup(data->comm->comm);
		if (new_instr == NULL)
			return (1);
		freedata(data);
		data->instr = new_instr;
		pars_and_launch(data, 0);
	}
	else if (tmp_dt->fd[1])
	{
		if (close(tmp_dt->fd[1]))
			ft_putstr_fd("Error close\n", 2);
		tmp_dt->fd[1] = 0;
	}
	return (wait_process_and_set_next_ptr(data));
}

int	check_parenthesis(int c, t_data *data, t_comm *tmp_dt)
{
	if (data->comm->status == 1)
		return (parenthesis_logic(c, data, tmp_dt));
	return (0);
}
