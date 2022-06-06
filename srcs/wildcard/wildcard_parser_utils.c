/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_parser_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:36 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:37 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	write_pos_wild(int **pos, int i, int a)
{
	int	*tmp;
	int	x;

	x = 0;
	tmp = malloc(sizeof(int) * (a + 1));
	if (!tmp)
		return (1);
	if (a > 1)
	{
		x = -1;
		while (++x < a - 1)
			tmp[x] = (*pos)[x];
	}
	tmp[x] = i;
	tmp[x + 1] = -1;
	if (*pos)
		free(*pos);
	*pos = tmp;
	return (0);
}

int	take_pos_for_wild(char **str, int **pos)
{
	int		n;
	int		i;

	n = 0;
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == -42)
		{
			(*str)[i] = '*';
			if (write_pos_wild(pos, i, ++n))
				return (1);
		}
	}
	return (0);
}

int	write_arg_wild(char ***args, char **wild, int a)
{
	char	**tmp;
	int		x;
	int		y;

	x = 0;
	y = a;
	while (wild[x])
		x++;
	while ((*args)[y])
		y++;
	tmp = malloc(sizeof(char *) * (x + y + 1));
	if (!tmp)
		return (1);
	x = -1;
	while (++x != a)
		tmp[x] = (*args)[x];
	y = -1;
	while (wild[++y])
		tmp[x++] = wild[y];
	while ((*args)[++a])
		tmp[x++] = (*args)[a];
	tmp[x] = NULL;
	free(*args);
	*args = tmp;
	return (0);
}
