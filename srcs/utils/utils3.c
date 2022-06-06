/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:25 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 09:33:11 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirect(char *op)
{
	if (is_same_lines(op, "<<"))
		return (1);
	if (is_same_lines(op, ">>"))
		return (1);
	if (is_same_lines(op, "<"))
		return (1);
	if (is_same_lines(op, ">"))
		return (1);
	return (0);
}

int	duplicate_fd(t_comm *data, int idx, int count_comm)
{
	if (idx == 0)
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	else if (idx + 1 == count_comm)
	{
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
			return (1);
	}
	else
	{
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
			return (1);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

int	initialize_dirs(char ***dirs, t_data *data, int *i)
{
	t_envr	*var;

	*i = -1;
	var = take_path_env(&data->env, "PATH");
	if (var == NULL)
		return (1);
	*dirs = ft_split(var->val, ':');
	if (*dirs == NULL)
		return (1);
	return (0);
}

int	check_access(t_comm *dt, t_data *data)
{
	if (access(dt->next->comm, 0) == 0)
	{
		if (is_redirect(data->comm->oper) && access(dt->next->comm, 4) != 0)
			return (ft_perror(dt));
	}
	else if (is_same_lines(dt->oper, "<"))
		return (ft_perror(dt));
	return (0);
}

int	check_oper(t_data *data)
{
	t_comm	*dt;
	int		err;

	dt = data->comm;
	if (is_same_lines(dt->comm, "export"))
		create_pipe(data->comm);
	if (is_same_lines(dt->oper, "|") || is_same_lines(dt->oper, "<<"))
	{
		if (is_same_lines(dt->oper, "<<"))
			err = exec_heredoc(&dt);
		else
			err = create_pipe(dt);
		if (err)
			return (err);
	}
	if (check_operator(dt) && is_redirect(dt->oper))
	{
		err = check_access(dt, data);
		if (err)
			return (err);
		if (create_pipe(dt->next))
			return (PIPE_ERR);
	}
	return (0);
}
