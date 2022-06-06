/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:34 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:05:35 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_result_and_line(char **line, char **result)
{
	*result = ft_calloc(1, sizeof(char));
	if (*result == NULL)
		return (1);
	*line = ft_calloc(1, sizeof(char));
	if (*line == NULL)
		return (1);
	return (0);
}

int	readline_and_free(char **line)
{
	free(*line);
	*line = readline("> ");
	if (*line == NULL)
		return (1);
	return (0);
}

int	init_line_with_nl(char **line_with_nl, char **line, char **result)
{
	*line_with_nl = ft_strjoin(*line, "\n");
	if (*line_with_nl == NULL)
	{
		free(*line);
		free(*result);
		return (1);
	}
	return (0);
}

int	heredoc(t_comm *data)
{
	char	*line;
	char	*ptr_to_free;
	char	*result;
	char	*line_with_nl;

	if (init_result_and_line(&result, &line))
		return (1);
	while (1)
	{
		if (readline_and_free(&line))
			return (1);
		if (is_same_lines(data->next->comm, line))
			break ;
		if (init_line_with_nl(&line_with_nl, &line, &result))
			return (1);
		if (init_result(\
		&ptr_to_free, &line_with_nl, &line, &result))
			return (1);
	}
	free(line);
	write(data->fd[1], result, ft_strlen(result));
	free(result);
	return (0);
}

int	duplicate_fd_for_heredoc(t_comm *data)
{
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		return (DUP_ERR);
	return (0);
}
