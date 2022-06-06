/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:19 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:05:20 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_one_list(t_envr **env)
{
	free((*env)->key);
	free((*env)->val);
	free (*env);
}

void	ft_unset_del(t_envr **p2, t_envr **envar, char *arg)
{
	t_envr	*p1;

	p1 = *envar;
	if (is_same_lines(p1->key, arg))
	{
		*envar = (*envar)->next;
		free_one_list(&p1);
		return ;
	}
	while (p1->next != *p2)
		p1 = p1->next;
	if ((*p2)->next == NULL)
	{
		free_one_list(p2);
		p1->next = NULL;
	}
	else
	{
		p1->next = (*p2)->next;
		free_one_list(p2);
	}
	return ;
}

void	ft_unset(t_data	*data)
{
	t_envr	*p2;
	int		i;

	i = 1;
	while (data->comm->args[i])
	{
		p2 = take_path_env(&data->env, data->comm->args[i]);
		if (p2)
			ft_unset_del(&p2, &data->env, data->comm->args[i]);
		p2 = take_path_env(&data->vars, data->comm->args[i]);
		if (p2)
			ft_unset_del(&p2, &data->vars, data->comm->args[i]);
		i++;
	}
}

int	check_right_var(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(*arg) && (*arg) != '_')
		return (1);
	while (arg[i] && arg[i] != '=')
		if (!ft_isalnum(arg[i++]) && (*arg) != '_')
			return (1);
	return (0);
}
