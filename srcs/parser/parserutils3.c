/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserutils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:07 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:08 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*delete_hashtag(char *str)
{
	char	**split;
	char	*res;
	int		i;

	if (!ft_strlen(str))
		return (str);
	split = ft_split(str, '#');
	res = split[0];
	i = 0;
	while (split[++i])
		free(split[i]);
	free(split);
	free(str);
	return (res);
}

int	checkallcommands(t_comm **p)
{
	t_comm	*tmp;

	tmp = *p;
	if (!tmp || (!tmp->comm && !tmp->args[1] && !tmp->oper))
		return (0);
	while (tmp)
	{
		if (tmp->oper && !tmp->next)
		{
			if (!tmp->comm)
				printf("🔥mini_hell🔥: syntax error near unexpected token `%s'\n"\
				, tmp->oper);
			else
				printf("🔥mini_hell🔥: syntax error: unexpected end of file\n");
			errno = 258;
			return (1);
		}
		if (check_wildcard(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	vars_quote_check(char **str, char **s, int i, t_comm *data)
{
	char	quote;

	if ((*s)[i] == '$' && data->prev && is_same_lines(data->prev->oper, "<<"))
		return (++i);
	if ((*s)[i] == '$' && (*s)[i + 1] && !ft_space((*s)[i + 1]) \
		&& (*s)[i + 1] != '=')
		return (takevar(s, str, data, i));
	if ((*s)[i] == 34 || (*s)[i] == 39)
	{
		quote = (*s)[i];
		if (check_second_qoute(*s, i, quote))
		{
			if (write_arg(str, s, i))
				return (-1);
			(*s)++;
			i = check_quote(s, str, quote, data);
			if (i < 0)
				return (-1);
			i = -1;
			(*s)++;
		}
	}
	if ((*s)[i] == '*')
		(*s)[i] = '*' * -1;
	return (++i);
}

int	print_error_and_errno(char *str, int error, int ret)
{
	printf("%s\n", str);
	errno = error;
	return (ret);
}
