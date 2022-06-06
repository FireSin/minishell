/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:23 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 19:46:51 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipes(t_comm *data)
{
	while (data->next)
	{
		if (pipe(data->fd) == -1)
			return (1);
		data = data->next;
	}
	return (0);
}

void	add_ptr_prev_to_data(t_comm *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	data->prev = NULL;
	while (data->next)
	{
		data->i = i++;
		data->next->prev = data;
		data = data->next;
	}
	data->i = i;
}

int	close_fd(t_comm *data)
{
	while (data && data->prev)
		data = data->prev;
	while (data->next)
	{
		if (data->fd[0] && data->fd[1])
		{
			if (close(data->fd[0]) == -1)
				return (1);
			if (close(data->fd[1]) == -1)
				return (1);
		}
		data = data->next;
	}
	return (0);
}

int	is_correct_comm(char *comm)
{
	if (comm && (comm[0] == '/' || comm[0] == '.' \
	|| (comm[0] == '.' && comm[1] == '/')) && !access(comm, 1))
		return (1);
	return (0);
}

int	is_same_lines(char *f_str, char *s_str)
{
	int	i;

	if (!f_str || !s_str)
		return (0);
	if (ft_strlen(f_str) != ft_strlen(s_str))
		return (0);
	i = -1;
	while (f_str[++i])
		if (f_str[i] != s_str[i])
			return (0);
	return (1);
}
