/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:12 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 15:36:32 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_argv(int argc, char **argv, char **env, t_data *data)
{
	(void) data;
	(void) env;
	if (argc != 1)
	{
		printf("mini_hell: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	return (0);
}

void	print_last_exit(void)
{
	printf("mini_hell: %d: %s\n", errno, strerror(errno));
}

void	fill_zero(int *arr, int k, int *j, char **res)
{
	(*j)--;
	if (*j < 0)
		*j = 0;
	else
		if (arr[--k] == (int)ft_strlen(res[*j]))
			res[*j][ft_strlen(res[*j])] = 0;
	res[(*j) + 1] = NULL;
}

int	only_slash(char *path)
{
	while (path && *path)
		if (*path++ != '/')
			return (0);
	return (1);
}
