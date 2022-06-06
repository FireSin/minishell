/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:04 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 11:10:13 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	write_tilda(char **s)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(*s, 2, ft_strlen(*s) - 2);
	if (tmp == NULL)
		return (ft_putstr_fd("🔥mini_hell🔥: error malloc in parse\n", 2));
	free (*s);
	tmp2 = getenv("HOME");
	tmp3 = ft_strjoin(tmp2, "/");
	if (tmp3 == NULL)
		return (ft_putstr_fd("🔥mini_hell🔥: error malloc in parse\n", 2));
	*s = ft_strjoin(tmp3, tmp);
	free(tmp3);
	free(tmp);
	if (*s == NULL)
		return (ft_putstr_fd("🔥mini_hell🔥: error malloc in parse\n", 2));
	return (0);
}

int	check_tilda(t_comm **comm)
{
	t_comm	*tmp;
	int		i;

	tmp = *comm;
	while (tmp && tmp->comm)
	{
		i = 0;
		if (is_same_lines(tmp->comm, "~") || \
			(tmp->comm[0] == '~' && tmp->comm[1] == '/'))
			if (write_tilda(&tmp->comm))
				return (1);
		while (tmp->args && tmp->args[++i])
			if (is_same_lines(tmp->args[i], "~") || \
			(tmp->args[i][0] == '~' && tmp->args[i][1] == '/'))
				if (write_tilda(&tmp->args[i]))
					return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_space(char str)
{
	if (str == ' ' || str == '\f' || str == '\n')
		return (1);
	if (str == '\r' || str == '\t' || str == '\v')
		return (1);
	return (0);
}

int	take_arg_mass(char ***args, int a)
{
	int		i;
	char	**mass;

	i = -1;
	mass = ft_calloc(sizeof(char *), a + 2);
	if (!mass)
	{
		printf("🔥mini_hell🔥: error malloc in parse\n");
		errno = 12;
		return (1);
	}
	while (++i != a)
		mass[i] = (*args)[i];
	mass[i] = NULL;
	mass[i + 1] = NULL;
	free(*args);
	*args = mass;
	return (0);
}

t_envr	*search_var(char *tmp, t_envr *p, t_envr *vars)
{
	while (p && !is_same_lines(tmp, p->key))
		p = p->next;
	if (!p && vars)
	{
		p = vars;
		while (p && !is_same_lines(tmp, p->key))
			p = p->next;
	}
	return (p);
}
