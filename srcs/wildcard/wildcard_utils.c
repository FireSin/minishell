/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:40 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:41 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len(char **template)
{
	int	count;

	count = 0;
	while (template && template[count])
		count++;
	return (count);
}

int	initial_var(char ***split_template, \
t_finfo *dt, char *template, int *arr_int)
{
	*split_template = split_wild(template, arr_int);
	if (*split_template == NULL)
		return (1);
	dt->start = NULL;
	dt->finish = NULL;
	dt->between = NULL;
	return (0);
}

int	init_dt_start(t_finfo *dt, char *str, char ***split_template)
{
	dt->start = ft_strdup(str);
	if (dt->start == NULL)
	{
		free_arrs(*split_template);
		return (1);
	}
	return (0);
}

int	init_dt_finish(t_finfo *dt, char *str, char ***temp, int last_idx_str)
{
	dt->finish = ft_strdup(str);
	if (dt->finish == NULL)
	{
		free_arrs(*temp);
		return (1);
	}
	free((*temp)[last_idx_str]);
	(*temp)[last_idx_str] = NULL;
	return (0);
}

int	init_dt_between(t_finfo *dt, char ***split_template, int *i)
{
	int	j;

	dt->between = malloc(sizeof(char *) * (len(*split_template) + 1));
	if (dt->between == NULL)
	{
		free_arrs(*split_template);
		return (1);
	}
	j = 0;
	while ((*split_template)[*i])
	{
		dt->between[j] = ft_strdup((*split_template)[(*i)++]);
		if (dt->between[j] == NULL)
		{
			free_arrs(*split_template);
			return (1);
		}
		j++;
	}
	dt->between[j] = NULL;
	return (0);
}
