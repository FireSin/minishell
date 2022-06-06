/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_local_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:09 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:10 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_var(char **trm, char **str)
{
	int	a;

	a = 0;
	while (trm[a] && (trm[a][0] != '<' || trm[a][0] != '>' \
		|| trm[a][0] != '&' || trm[a][0] != '|'))
	{
		if (!ft_strchr(trm[a], '=') || check_right_var(trm[a]))
		{
			a = 0;
			break ;
		}
		while (**str && !ft_space(**str) && (**str != '<' || **str != '>' \
		|| **str != '&' || **str != '|'))
			(*str)++;
		while (**str && ft_space(**str))
			(*str)++;
		a++;
	}
	return (a);
}

t_envr	*check_path_in_local_and_env(t_data *data, char *key)
{
	t_envr	*rv;

	rv = take_path_env(&data->env, key);
	if (!rv)
		rv = take_path_env(&data->vars, key);
	return (rv);
}

int	check_in_env(t_data *data, char *var)
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
	rv = check_path_in_local_and_env(data, tmp_key);
	if (!rv)
	{
		free(tmp_key);
		free(tmp_val);
		return (-1);
	}
	free(tmp_key);
	free(rv->val);
	rv->val = tmp_val;
	return (0);
}

int	check_in_env_and_write(t_data *data, char **trm, int a)
{
	int	i;

	while (a > 0)
	{
		i = check_in_env(data, trm[--a]);
		if (i)
		{
			if (i == 1 || add_list_env(&data->vars, trm[a]))
			{
				errno = 12;
				return (1);
			}
		}
	}
	return (0);
}

int	check_for_local_vars(char **str, t_data *data)
{
	int		a;
	int		i;
	char	**trm;

	while (**str && ft_space(**str))
		(*str)++;
	if (data->comm || !(**str))
		return (0);
	trm = ft_split(*str, ' ');
	if (!trm)
	{
		printf("🔥mini_hell🔥: error malloc in parse\n");
		errno = 12;
		return (1);
	}
	a = check_for_var(trm, str);
	i = check_in_env_and_write(data, trm, a);
	free_arrs(trm);
	return (i);
}
