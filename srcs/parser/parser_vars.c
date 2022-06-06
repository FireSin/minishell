/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:57 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:05:58 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_another_after_var(char **s, char **str)
{
	char	*tmp;
	char	*tmp2;

	if (varisdigit(s))
		return (0);
	if (**s == '?')
		return (last_error(s, str));
	if (**s == '$')
	{
		(*s)++;
		tmp = ft_itoa(getpid());
		if (!tmp)
			return (-1);
		tmp2 = *str;
		*str = ft_strjoin(tmp2, tmp);
		if (!(*str))
			return (-1);
		return (0);
	}
	return (-100);
}

int	takevar(char **s, char **str, t_comm *data, int i)
{
	char	*tmp;
	t_envr	*p;

	tmp = NULL;
	if (i > 0 && write_arg(str, s, i))
		return (-1);
	p = data->data->env;
	(*s)++;
	i = check_another_after_var(s, str);
	if (i != -100)
		return (i);
	i = 0;
	while ((*s)[i] && ((*s)[i] == '_' || ft_isalnum((*s)[i])))
		i++;
	tmp = ft_substr(*s, 0, i);
	if (!tmp)
		return (-1);
	p = search_var(tmp, p, data->data->vars);
	if (p)
		if (writevar(str, *p))
			return (-1);
	while (i--)
		(*s)++;
	free(tmp);
	return (0);
}

int	ft_create_var(t_data *data, char *var)
{
	t_envr	*p;

	if (!ft_isalpha(*var))
		return (printf("🔥mini_hell🔥: %s: command not found\n", var));
	p = malloc(sizeof(t_envr));
	if (!p)
	{
		errno = 12;
		return (printf("🔥mini_hell🔥: error malloc in export\n"));
	}
	write_start_env(var, &p);
	if (!p->key || !p->val)
	{
		errno = 12;
		return (printf("🔥mini_hell🔥: error malloc in export\n"));
	}
	p->next = data->vars;
	data->vars = p;
	return (0);
}
