/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:00 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:01 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	takecommand(t_comm *data, char **s)
{
	int		i;

	while (**s && !data->comm && !data->oper)
	{
		i = 0;
		while ((*s)[i] && i >= 0 && !ft_space((*s)[i]) \
			&& operand(data, s, &i, &data->comm) && \
			!check_prnts(&data->comm, s, &i, data))
			i = vars_quote_check(&data->comm, s, i, data);
		if (i < 0 || (i > 0 && write_arg(&data->comm, s, i)))
			return (1);
		while (**s && ft_space(**s))
			(*s)++;
	}
	return (0);
}

int	takeargs(t_comm *data, char **s)
{
	int	i;
	int	a;

	a = 1;
	while ((*s)[0] && !data->oper)
	{
		i = 0;
		while ((*s)[i] && i >= 0 && !ft_space((*s)[i]) \
			&& operand(data, s, &i, &data->args[a]) && \
			!check_prnts(&data->comm, s, &i, data))
			i = vars_quote_check(&data->args[a], s, i, data);
		if (i < 0 || (i > 0 && write_arg(&data->args[a], s, i)))
			return (1);
		while ((**s) && ft_space(**s))
			(*s)++;
		while (data->args[a])
			a++;
		if (take_arg_mass(&data->args, a))
			return (1);
	}
	return (0);
}

int	free_str(char *str)
{
	free(str);
	return (1);
}

int	check_null_command(t_comm *p)
{
	if (!p->comm && !p->oper)
	{
		p->comm = ft_strdup(" ");
		if (!p->comm)
			return (print_error_and_errno("Error malloc in parse", 12, 1));
	}
	return (0);
}

int	parser(t_data *data, int i)
{
	t_comm	*p;
	char	*str;
	char	*tmp;

	str = ft_strdup(data->instr);
	if (!str)
		return (print_error_and_errno("Error malloc in parse", 12, 1));
	tmp = str;
	while (*str)
	{
		if (check_for_local_vars(&str, data))
			return (free_str(tmp));
		if (!(*str))
			break ;
		p = addelem(data, i);
		if (!p)
			return (print_error_and_errno("Error malloc in parse", 12, 1));
		if (takecommand(p, &str))
			return (free_str(tmp));
		if (!p->oper)
			if (takeargs(p, &str) || check_null_command(p))
				return (free_str(tmp));
	}
	free(tmp);
	return (checkallcommands(&data->comm));
}
