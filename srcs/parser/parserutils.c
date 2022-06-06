/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:02 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:03 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntx_oper(char **arg, char **s, int *i, int a)
{
	if (*i > 0 && write_arg(arg, s, *i))
	{
		*i = -1;
		return (0);
	}
	while (a--)
		(*s)++;
	*i = 0;
	if (**s == '<' || **s == '>' || **s == '|' || **s == '&')
	{
		printf("🔥mini_hell🔥: syntax error near unexpected token `%c\'\n", **s);
		*i = -2;
	}
	return (0);
}

int	operand(t_comm	*data, char **s, int *i, char **arg)
{
	int	a;

	a = 0;
	if ((*s)[*i] == '<' || (*s)[*i] == '>' || (*s)[*i] == '|')
	{
		if ((*s)[*i] == (*s)[*i + 1])
			a++;
		data->oper = ft_substr(*s, *i, ++a);
	}
	if ((*s)[*i] == '&' && (*s)[*i + 1] == '&')
	{
		a = 2;
		data->oper = ft_substr(*s, *i, a);
	}
	if (a > 0)
		return (syntx_oper(arg, s, i, a));
	return (1);
}

int	check_quote(char **s, char **str, char quote, t_comm *data)
{
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != quote)
	{
		if (quote == 34 && (*s)[i] == '$' && (*s)[i + 1] \
			&& !ft_space((*s)[i + 1]) && (*s)[i + 1] != '=')
		{
			if (data->prev && is_same_lines(data->prev->oper, "<<"))
				i++;
			else
			{
				i = takevar(s, str, data, i);
				if (i < 0)
					return (-1);
			}
		}
		else
			i++;
	}
	if (write_arg(str, s, i))
		return (-1);
	return (i);
}

int	write_arg(char **arg, char **s, int i)
{
	char	*tmp1;
	char	*tmp2;

	if (!*arg && i == 0)
		return (0);
	if (!ft_strlen(*arg))
		*arg = ft_substr(*s, 0, i);
	else
	{
		tmp1 = *arg;
		tmp2 = ft_substr(*s, 0, i);
		if (!tmp2)
			return (1);
		*arg = ft_strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
	}
	if (!(*arg))
	{
		errno = 12;
		return (1);
	}
	while (i--)
		(*s)++;
	return (0);
}

int	check_second_qoute(char *s, int i, char quote)
{
	while (s[++i])
		if (s[i] == quote)
			return (1);
	return (0);
}
