/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:28 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 15:52:05 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_index(t_comm *dt)
{
	int	i;

	i = 0;
	while (dt)
	{
		dt->i = i++;
		dt = dt->next;
	}
}

void	increment_shlvl(t_data *data)
{
	t_envr	*env;
	char	*ptr_to_free;

	env = data->env;
	while (env)
	{
		if (is_same_lines(env->key, "SHLVL"))
		{
			ptr_to_free = env->val;
			env->val = ft_itoa(ft_atoi(env->val) + 1);
			free(ptr_to_free);
			break ;
		}
		env = env->next;
	}
}

void	write_start_env(char *envar, t_envr **temp)
{
	char	**tmp;

	tmp = ft_split(envar, '=');
	(*temp)->key = tmp[0];
	(*temp)->val = tmp[1];
	free(tmp);
}

void	take_start_env(t_data *data, char **envar)
{
	t_envr	*temp;
	int		a;

	a = -1;
	while (envar[++a])
	{
		temp = (t_envr *)malloc(sizeof(t_envr));
		if (!temp)
		{
			errno = 12;
			error_mes_with_exit("Error malloc in write env\n", data);
		}
		write_start_env(envar[a], &temp);
		if (!temp->key)
		{
			errno = 12;
			error_mes_with_exit("Error malloc in write env\n", data);
		}
		temp->next = data->env;
		data->env = temp;
	}
}

int	set_next_dt(t_data *data)
{
	while (data->comm && !is_logic_oper(data->comm->oper))
		data->comm = data->comm->next;
	return (1);
}
