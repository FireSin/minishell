/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:17 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:18 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_operator(t_comm *dt)
{
	if (dt->next)
		if (is_same_lines(dt->next->oper, "|") && \
		(is_same_lines(dt->oper, "<<") || is_same_lines(dt->oper, "<")))
			return (1);
	if (is_same_lines(dt->oper, "<") || \
	is_same_lines(dt->oper, ">") || is_same_lines(dt->oper, ">>"))
		return (1);
	return (0);
}

void	ft_fprintf(char *command, char *str)
{
	write(2, "🔥mini_hell🔥: ", 20);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
}

int	create_pipe(t_comm *data)
{
	if (pipe(data->fd) == -1)
		return (1);
	return (0);
}
