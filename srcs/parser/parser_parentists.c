/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parentists.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:53 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:05:54 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_couple_pr(char *s)
{
	int	open;
	int	close;
	int	i;

	i = -1;
	open = 0;
	close = 0;
	while (s[++i])
	{
		if (s[i] == ')')
			close++;
		if (s[i] == '(')
			open++;
	}
	if (close != open)
		return (1);
	return (0);
}

int	write_new_instr(char **old_instr, char **new_instr)
{
	int		i;
	int		prnt;

	i = 0;
	prnt = 1;
	while ((*old_instr)[++i] && prnt != 0)
	{
		if ((*old_instr)[i] == '(')
			prnt++;
		if ((*old_instr)[i] == ')')
			prnt--;
	}
	*new_instr = ft_substr(*old_instr, 1, i - 2);
	if (!(*new_instr))
		return (1);
	while (i--)
		(*old_instr)++;
	return (0);
}

int	check_prnts(char **str, char **s, int *i, t_comm *data)
{
	char	*new_instr;

	if ((*s)[*i] != ')' && (*s)[*i] != '(')
		return (0);
	if ((*s)[*i] == ')' || data->comm)
	{
		*i = -1;
		printf("syntax error near unexpected token `)'\n");
		return (1);
	}
	if (check_couple_pr(*s))
	{
		*i = -1;
		printf("syntax error: unexpected end of file\n");
		return (1);
	}
	if (write_arg(str, s, *i) || write_new_instr(s, &new_instr))
	{
		*i = -1;
		return (1);
	}
	data->comm = new_instr;
	*i = 0;
	data->status = 1;
	return (1);
}
