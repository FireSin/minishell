/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:29 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:05:30 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redirect(t_data *data)
{
	if (is_same_lines(data->comm->oper, ">"))
		return (1);
	if (is_same_lines(data->comm->oper, ">>"))
		return (1);
	return (0);
}

int	init_result(char **free_ptr, char **nl, char **line, char **res)
{
	*free_ptr = *res;
	*res = ft_strjoin(*res, *nl);
	free(*nl);
	free(*free_ptr);
	if (*res == NULL)
	{
		free(*line);
		return (1);
	}
	return (0);
}

int	exec_heredoc(t_comm **data)
{
	t_comm	*dt;

	dt = *data;
	while (dt && ((is_same_lines(dt->oper, "<<")) || \
	(dt->next && is_same_lines(dt->next->oper, "|") \
	&& is_same_lines(dt->oper, "<<"))))
	{
		dt->fd[1] = open("/tmp/.tmp_heredoc", \
		O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (dt->fd[1] == -1)
			return (OPEN_ERR);
		if (create_pipe(dt))
			return (PIPE_ERR);
		if (heredoc(dt))
			return (MALLOC_ERR);
		if (dt->next && is_same_lines(dt->next->oper, "|") \
		&& is_same_lines(dt->oper, "<<"))
			dt = dt->next->next;
		else
			dt = dt->next;
	}
	return (0);
}

int	next_oper(char *oper)
{
	if (is_same_lines(oper, "<<"))
		return (1);
	if (is_same_lines(oper, "|"))
		return (1);
	return (0);
}

int	curr_oper(char *oper)
{
	if (is_same_lines(oper, "<"))
		return (1);
	return (0);
}
