/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:09 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:05:10 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envr	*take_path_env(t_envr **env, char *s)
{
	t_envr	*p;

	p = *env;
	while (p)
	{
		if (is_same_lines(p->key, s))
			return (p);
		p = p->next;
	}
	return (NULL);
}

int	ft_cd_with_home(t_data *data)
{
	char	*path;
	t_envr	*pwd;
	t_envr	*oldpwd;

	pwd = take_path_env(&data->env, "PWD");
	oldpwd = take_path_env(&data->env, "OLDPWD");
	path = data->comm->args[1];
	path = ft_strjoin(getenv("HOME"), (path + 1));
	if (!path)
		return (printf("🔥mini_hell🔥: error malloc cd\n"));
	if (chdir(path))
	{
		free (path);
		return (printf("🔥mini_hell🔥: cd: %s: %s\n", \
		data->comm->args[1], strerror(errno)));
	}
	oldpwd->val = pwd->val;
	pwd->val = path;
	return (0);
}

int	ft_cd_prev_dir(t_data *data)
{
	char	*path;
	t_envr	*pwd;
	t_envr	*oldpwd;

	pwd = take_path_env(&data->env, "PWD");
	oldpwd = take_path_env(&data->env, "OLDPWD");
	path = oldpwd->val;
	if (!is_same_lines(data->comm->args[1], "-"))
		return (printf("🔥mini_hell🔥: cd: %s: %s\n", \
		data->comm->args[1], strerror(errno)));
	if (!path)
		return (printf("🔥mini_hell🔥: cd: OLDPWD not set\n"));
	if (chdir(path))
		return (printf("🔥mini_hell🔥: cd: %s: %s\n", \
		data->comm->args[1], strerror(errno)));
	oldpwd->val = pwd->val;
	pwd->val = path;
	printf("%s\n", pwd->val);
	return (0);
}

int	ft_cd_without_arg(t_data *data)
{
	t_envr	*pwd;
	t_envr	*oldpwd;

	pwd = take_path_env(&data->env, "PWD");
	oldpwd = take_path_env(&data->env, "OLDPWD");
	if (chdir(getenv("HOME")))
		return (printf("🔥mini_hell🔥: cd: %s: %s\n", \
		data->comm->args[1], strerror(errno)));
	free (oldpwd->val);
	oldpwd->val = pwd->val;
	pwd->val = ft_strdup(getenv("HOME"));
	if (!pwd->val)
		return (printf("🔥mini_hell🔥: error malloc cd\n"));
	return (0);
}

int	ft_cd(t_data *data)
{
	t_envr	*pwd;
	t_envr	*oldpwd;
	char	cwd[PATH_MAX];

	if (!(data->comm->args[1]))
		return (ft_cd_without_arg(data));
	if (data->comm->args[1][0] == '-')
		return (ft_cd_prev_dir(data));
	if (data->comm->args[1][0] == '~')
		return (ft_cd_with_home(data));
	pwd = take_path_env(&data->env, "PWD");
	oldpwd = take_path_env(&data->env, "OLDPWD");
	if (chdir(data->comm->args[1]))
		return (printf("cd: %s: %s\n", data->comm->args[1], strerror(errno)));
	free(oldpwd->val);
	oldpwd->val = pwd->val;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (printf("Error take cwd\n"));
	pwd->val = ft_strdup(cwd);
	if (!pwd->val)
		return (printf("Error malloc cd\n"));
	return (0);
}
