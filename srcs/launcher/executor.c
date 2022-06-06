/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:32 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 15:36:53 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe(t_data *data)
{
	if (is_same_lines(data->comm->oper, "|"))
		return (1);
	if (data->comm->prev && is_same_lines(data->comm->prev->oper, "|"))
		return (1);
	return (0);
}

int	handle_heredoc(t_comm *data, int count_comm)
{
	int	res;

	res = 0;
	while (data && is_same_lines(data->oper, "<<"))
	{
		if (duplicate_fd_for_heredoc(data) == DUP_ERR)
			return (DUP_ERR);
		data = data->next;
	}
	if (data && data->next && is_same_lines(data->next->oper, "|"))
		res = duplicate_fd(data->next, data->next->i, count_comm);
	else if (data && is_same_lines(data->oper, ">"))
		res = redirect_out(data);
	return (res);
}

int	handle_oper(t_data *data, int count_comm)
{
	int	res;

	res = 0;
	if (check_redirect(data))
		res = redirect_out(data->comm);
	else if (is_same_lines(data->comm->oper, "<"))
		res = redirect_in(data->comm);
	else if (check_pipe(data))
		res = duplicate_fd(data->comm, data->comm->i, count_comm);
	else if (is_same_lines(data->comm->oper, "<<"))
		res = handle_heredoc(data->comm, count_comm);
	if (res)
		return (res);
	if (curr_oper(data->comm->oper) && \
	data->comm->next && next_oper(data->comm->next->oper))
		res = duplicate_fd(data->comm->next, data->comm->next->i, count_comm);
	else if (data->comm->next && \
	(is_same_lines(data->comm->next->oper, ">") || \
	is_same_lines(data->comm->next->oper, ">>")))
		if (!is_same_lines(data->comm->oper, "|"))
			res = redirect_out(data->comm->next);
	return (res);
}

void	exec_command(t_data *data, char *path)
{
	if (data->comm->prev && data->comm->prev->prev \
	&& is_same_lines(data->comm->prev->prev->oper, "<<"))
		if (dup2(data->comm->prev->fd[0], STDIN_FILENO) == -1)
			exit(DUP_ERR);
	if (close_fd(data->comm))
		exit(CLOSE_ERR);
	if (is_same_lines("launch builtins", path))
		exit(launch_builtins(data));
	else
	{
		if (execve(path, data->comm->args, get_env(data->env)) == -1)
		{
			perror(path);
			exit(errno);
		}
	}
	exit(0);
}

int	executor(t_data *data, char *path, int count_comm)
{
	int		error;

	error = check_oper(data);
	data->comm->pid = fork();
	if (data->comm->pid < 0)
		return (FORK_ERR);
	else if (data->comm->pid == 0)
	{
		if (error)
		{
			errno = error;
			exit(error);
		}
		error = handle_oper(data, count_comm);
		if (error)
			exit(error);
		if (data->comm->comm)
			exec_command(data, path);
		else
			exit(0);
	}
	return (0);
}
