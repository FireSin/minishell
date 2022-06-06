/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:43 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:05:44 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_fd(t_comm *data, int *fd)
{
	if (is_same_lines(data->oper, ">"))
		*fd = open(data->next->comm, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		*fd = open(data->next->comm, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
}

int	check_duplicate(int *fd, t_comm *data)
{
	if (dup2(*fd, STDOUT_FILENO) == -1)
		return (DUP_ERR);
	if (data && data->prev && is_same_lines(data->prev->oper, "|"))
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
			return (DUP_ERR);
	if (data && data->prev && is_same_lines(data->prev->oper, "<"))
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
			return (DUP_ERR);
	return (0);
}

int	redirect_out(t_comm *data)
{
	int	fd;
	int	err;

	fd = 0;
	while (data && (is_same_lines(data->oper, ">") \
	|| is_same_lines(data->oper, ">>")))
	{
		if (fd)
			if (close(fd) == -1)
				return (CLOSE_ERR);
		init_fd(data, &fd);
		if (fd == -1)
			return (OPEN_ERR);
		err = check_duplicate(&fd, data);
		if (err)
			return (err);
		if (data && data->next && is_same_lines(data->next->oper, "<"))
		{
			err = redirect_in(data->next);
			if (err)
				return (err);
		}
		data = data->next;
	}
	return (close(fd));
}

int	redirect_in(t_comm *data)
{
	int	fd;

	fd = 0;
	while (data && is_same_lines(data->oper, "<"))
	{
		if (fd)
			if (close(fd) == -1)
				return (CLOSE_ERR);
		fd = open(data->next->comm, O_RDONLY);
		if (fd == -1)
			return (OPEN_ERR);
		data = data->next;
	}
	data = data->next;
	if (dup2(fd, STDIN_FILENO) == -1)
		return (DUP_ERR);
	if (data && data->next && is_same_lines(data->next->oper, "|"))
		if (dup2(data->next->fd[1], STDOUT_FILENO) == -1)
			return (DUP_ERR);
	if (data && data->prev && is_same_lines(data->prev->oper, ">"))
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (DUP_ERR);
	return (0);
}
