/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_move_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:51 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 19:43:20 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	rewrite_args(char ***in, char **out)
{
	int		x;
	int		y;
	char	**tmp;

	x = len(*in);
	y = len(out);
	tmp = malloc(sizeof(char *) * (x + y + 1));
	if (!tmp)
		return (1);
	x = -1;
	while ((*in)[++x])
		tmp[x] = (*in)[x];
	y = -1;
	while (out[++y])
	{
		tmp[x++] = out[y];
		out[y] = NULL;
	}
	tmp[x] = NULL;
	free (*in);
	*in = tmp;
	return (0);
}

int	move_args_loop(t_comm **p, t_comm **tmp)
{
	char	**arg;
	int		i;

	i = 0;
	arg = (*tmp)->args;
	arg++;
	if (!(*p)->comm && arg[0])
	{
		(*p)->comm = arg[0];
		arg++;
	}
	if (*arg && (*tmp)->prev)
		if (rewrite_args(&(*p)->args, arg))
			return (1);
	while ((*tmp)->args[++i] && (*tmp)->prev)
		(*tmp)->args[i] = NULL;
	return (0);
}

int	move_args(t_comm **p, t_comm **tmp)
{
	if ((*tmp)->prev && (*tmp)->prev->oper && \
	!((*tmp)->prev->oper[0] == '>' || (*tmp)->prev->oper[0] == '<'))
	{
		if ((*p)->comm)
			*p = (*p)->next;
		return (0);
	}
	if ((((*tmp)->oper && (*tmp)->oper[0] == '>') \
	|| ((*tmp)->prev && (*tmp)->prev->oper && (*tmp)->prev->oper[0] == '>')) \
	|| (((*tmp)->oper && (*tmp)->oper[0] == '<') \
	|| ((*tmp)->prev && (*tmp)->prev->oper && (*tmp)->prev->oper[0] == '<')))
	{
		if (move_args_loop(p, tmp))
			return (1);
	}
	else if ((*p)->comm)
		*p = (*p)->next;
	return (0);
}

int	check_for_move_arg(t_box **box)
{
	t_comm	*tmp;
	t_comm	*start;
	t_box	*btmp;

	btmp = *box;
	tmp = (*box)->dt_comm;
	start = tmp;
	while (btmp)
	{
		while (tmp)
		{
			if (move_args(&start, &tmp))
				return (1);
			tmp = tmp->next;
		}
		btmp = btmp->next;
	}
	return (0);
}
