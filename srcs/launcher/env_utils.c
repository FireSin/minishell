/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:27 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 10:55:58 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_fsize(int fd)
{
	struct stat	buff;

	if (fstat(fd, &buff) == -1)
		return (-1);
	return (buff.st_size);
}

int	set_env(t_comm *data, t_data *dt)
{
	char	*buf;
	char	**split_str;
	int		i;
	int		size;

	size = get_fsize(data->fd[0]);
	if (size == -1)
		return (1);
	buf = malloc(size * sizeof(char));
	if (buf == NULL)
		return (1);
	if (read(data->fd[0], buf, size) == -1)
		return (1);
	split_str = ft_split(buf, '\n');
	if (split_str == NULL)
		return (1);
	free(buf);
	delenv(&dt->env);
	dt->env = NULL;
	take_start_env(dt, split_str);
	i = -1;
	while (split_str[++i])
		free(split_str[i]);
	free(split_str);
	return (0);
}

int	count_dict(t_envr *dt_env)
{
	int	i;

	i = 0;
	while (dt_env)
	{
		i++;
		dt_env = dt_env->next;
	}
	return (i + 1);
}

int	do_pair(char **key_with_equel, char **pair, char ***env, t_envr *dt_env)
{
	if (!dt_env->val)
	{
		*pair = ft_strdup(dt_env->key);
		if (*pair == NULL)
		{
			free_arrs(*env);
			return (1);
		}
		return (0);
	}
	*key_with_equel = ft_strjoin(dt_env->key, "=");
	if (*key_with_equel == NULL)
	{
		free_arrs(*env);
		return (1);
	}
	*pair = ft_strjoin(*key_with_equel, dt_env->val);
	if (*pair == NULL)
	{
		free_arrs(*env);
		free(*key_with_equel);
		return (1);
	}
	free(*key_with_equel);
	return (0);
}

char	**get_env(t_envr *dt_env)
{
	int		i;
	char	**env;
	char	*key_with_equel;
	char	*pair;

	i = 0;
	env = malloc(sizeof(char *) * count_dict(dt_env));
	if (env == NULL)
		return (NULL);
	while (dt_env)
	{
		if (do_pair(&key_with_equel, &pair, &env, dt_env))
			return (NULL);
		env[i++] = pair;
		dt_env = dt_env->next;
	}
	env[i] = NULL;
	return (env);
}
