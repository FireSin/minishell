/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:15 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:16 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_arrs(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
	}
	if (arr)
		free(arr);
	arr = NULL;
}

int	continue_with_print(char *err_str)
{
	printf("%s\n", err_str);
	return (1);
}

int	handle_error_executor(int error)
{
	if (error == PIPE_ERR)
		return (continue_with_print("Error: pipe() returned fail\n"));
	if (error == FORK_ERR)
		return (continue_with_print("Error: fork() returned fail\n"));
	if (error == DUP_ERR)
		return (continue_with_print("Error: dup2() returned fail\n"));
	if (error == CLOSE_ERR)
		return (continue_with_print("Error: close() returned fail\n"));
	if (error == EXEC_ERR)
		return (continue_with_print("Error: execve() returned fail\n"));
	if (error == MALLOC_ERR)
		return (continue_with_print("Error: malloc() returned fail\n"));
	if (error == OPEN_ERR)
		return (continue_with_print("Error: open() returned fail\n"));
	return (0);
}

int	ft_perror(t_comm *dt)
{
	write(2, "mini_hell: ", 11);
	perror(dt->next->comm);
	return (1);
}

int	del_file_doc(t_comm *data)
{
	t_comm	*dt;

	dt = data;
	while (dt)
	{
		if (dt->oper && is_same_lines(dt->oper, "<<"))
			return (unlink("/tmp/.tmp_heredoc"));
		dt = dt->next;
	}
	return (0);
}
