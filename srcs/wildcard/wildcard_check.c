/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:34 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:35 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_start(t_finfo *dt, char *filename)
{
	int	i;

	i = 0;
	while (dt->start[i] && filename[i])
	{
		if (dt->start[i] != filename[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_finish(t_finfo *dt, char *filename)
{
	int	last_idx_filename;
	int	dt_finish_idx;

	last_idx_filename = ft_strlen(filename) - 1;
	dt_finish_idx = ft_strlen(dt->finish) - 1;
	while (last_idx_filename >= 0 && dt_finish_idx >= 0)
		if (filename[last_idx_filename--] != dt->finish[dt_finish_idx--])
			return (1);
	return (0);
}

char	*get_fname_without_start(char *fname, t_finfo *dt)
{
	int	i;

	i = 0;
	while (dt->start && *fname == dt->start[i])
	{
		fname++;
		i++;
	}
	return (ft_strdup(fname));
}

char	*get_fname_without_start_and_finish(char *fname, t_finfo *dt)
{
	int		i;
	int		j;
	int		n;
	char	*res;

	i = 0;
	while (dt->start && fname[i] == dt->start[i])
		i++;
	n = ft_strlen(fname) - 1;
	j = ft_strlen(dt->finish) - 1;
	while (j >= 0 && dt->finish[j] == fname[n])
	{
		j--;
		n--;
	}
	res = ft_substr(fname, i, ft_strlen(fname) - \
	ft_strlen(dt->start) - ft_strlen(dt->finish));
	return (res);
}

int	check_between(t_finfo *dt, char *filename)
{
	int		i;
	int		j;
	char	*fname;
	char	*sub_str;

	i = 0;
	fname = get_fname_without_start_and_finish(filename, dt);
	if (fname == NULL)
		return (1);
	sub_str = fname;
	while (dt->between[i])
	{
		j = 0;
		sub_str = ft_strnstr(sub_str, dt->between[i], ft_strlen(sub_str));
		if (sub_str == NULL)
		{
			free(fname);
			return (1);
		}
		while (dt->between[i][j++])
			sub_str++;
		i++;
	}
	free(fname);
	return (0);
}
