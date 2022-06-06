/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:17 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 11:05:21 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_list_env(t_envr **env, char *arg)
{
	t_envr	*p;
	int		i;

	i = 0;
	if (!ft_strchr(arg, '='))
		return (0);
	p = malloc(sizeof(t_envr));
	if (!p)
	{
		printf("🔥mini_hell🔥: error malloc export\n");
		return (1);
	}
	while (arg[i] != '=')
		i++;
	p->key = ft_substr(arg, 0, i++);
	p->val = ft_substr(arg, i, ft_strlen(arg));
	if (!p->key || !p->val)
	{
		printf("🔥mini_hell🔥: error malloc export\n");
		return (1);
	}
	p->next = *env;
	*env = p;
	return (0);
}

void	print_env(t_envr *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->val)
			printf("=%s", env->val);
		printf("\n");
		env = env->next;
	}
}

int	seach_in_vars_with_eq(t_data *data, char *var, int *i)
{
	t_envr	*rv;
	char	*tmp_key;
	char	*tmp_val;
	int		n;

	n = 0;
	while (var[n] != '=')
		n++;
	tmp_key = ft_substr(var, 0, n++);
	tmp_val = ft_substr(var, n, ft_strlen(var));
	if (!tmp_key || !tmp_val)
		return (1);
	rv = take_path_env(&data->env, tmp_key);
	if (!rv)
	{
		free(tmp_key);
		free(tmp_val);
		return (-1);
	}
	free(tmp_key);
	free(rv->val);
	rv->val = tmp_val;
	(*i)++;
	return (0);
}

int	seach_in_vars(t_data *data, char *var, int *i)
{
	t_envr	*rv;
	t_envr	*tenv;

	if (ft_strchr(var, '='))
		return (seach_in_vars_with_eq(data, var, i));
	rv = take_path_env(&data->vars, var);
	tenv = malloc(sizeof(t_envr));
	if (!tenv)
		return (1);
	if (rv)
	{
		tenv->key = rv->key;
		tenv->val = rv->val;
	}
	else
	{
		tenv->key = ft_strdup(var);
		if (!tenv->key)
			return (1);
		tenv->val = NULL;
	}
	tenv->next = data->env;
	data->env = tenv;
	(*i)++;
	return (0);
}

int	ft_export(t_data *data)
{
	int		i;
	int		check;

	i = 1;
	if (!data->comm->args[i])
		print_env(data->env);
	while (data->comm->args[i])
	{
		if (check_right_var(data->comm->args[i]))
		{
			printf("🔥mini_hell🔥: export: '%s': not a valid identifier\n", \
			data->comm->args[i++]);
			continue ;
		}
		check = seach_in_vars(data, data->comm->args[i], &i);
		if (check == 1)
			return (1);
		if (!check)
			continue ;
		if (add_list_env(&data->env, data->comm->args[i++]))
			return (1);
	}
	return (0);
}
