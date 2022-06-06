/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:45 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:46 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	read_directory(DIR *dir, struct dirent **entry)
{
	*entry = readdir(dir);
	if (*entry == NULL)
		return (0);
	return (1);
}

int	get_last_idx_str(char **split_template)
{
	int	i;

	i = 0;
	while (split_template[i] && split_template[i + 1])
		i++;
	return (i);
}

int	init_dt(t_finfo *dt, char *template, int *arr_int)
{
	char	**split_template;
	int		i;
	int		last_idx_str;
	int		last_idx_char;

	if (initial_var(&split_template, dt, template, arr_int))
		return (1);
	i = 0;
	if (template[i] != '*')
		if (init_dt_start(dt, split_template[i++], &split_template))
			return (1);
	last_idx_char = ft_strlen(template) - 1;
	last_idx_str = get_last_idx_str(split_template);
	if (template[last_idx_char] != '*')
		if (init_dt_finish(dt, split_template[last_idx_str], \
		&split_template, last_idx_str))
			return (1);
	if (split_template[i])
		if (init_dt_between(dt, &split_template, &i))
			return (1);
	free_arrs(split_template);
	return (0);
}

int	is_right_file(char *filename, char *template, int *arr_int)
{
	t_finfo	*dt;
	int		i;
	int		count;

	if (filename[0] == '.' && template[0] != '.')
		return (0);
	dt = malloc(sizeof(t_finfo));
	if (dt == NULL)
		return (free_dt(dt));
	if (init_dt(dt, template, arr_int))
		return (free_dt(dt));
	i = 0;
	count = 0;
	while (dt->between && i < len(dt->between) && dt->between[i])
		count += ft_strlen(dt->between[i++]);
	if (ft_strlen(filename) < ft_strlen(dt->start) + \
	ft_strlen(dt->finish) + count)
		return (free_dt(dt));
	return (check_parts(dt, filename));
}

char	**wildcard(char *template, int *arr_int)
{
	char			**arr;
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	arr = NULL;
	i = 0;
	while (read_directory(dir, &entry))
		if (is_right_file(entry->d_name, template, arr_int))
			if (wild_add_elem(&arr, entry->d_name, i++))
				continue ;
	closedir(dir);
	if (arr == NULL)
	{
		arr = malloc(sizeof(char *) * 2);
		arr[0] = template;
		arr[1] = NULL;
	}
	else
		free(template);
	return (arr);
}
