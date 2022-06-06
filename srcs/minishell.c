/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:47 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 19:12:53 by rrast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_box(t_box *box, int i, t_data *data)
{
	t_box	*ptr;

	while (box)
	{
		ptr = box;
		data->comm = box->dt_comm;
		init_index(data->comm);
		if (launcher(data))
			break ;
		set_next_box(&box);
		freebox(&ptr);
	}
	if (i == 0)
		exit (errno);
}

void	pars_and_launch(t_data *data, int i)
{
	t_box	*box;

	box = NULL;
	data->comm = NULL;
	if (parser(data, i) || check_tilda(&data->comm))
	{
		freedata(data);
		return ;
	}
	if (init_containers(data->comm, &box))
		return ;
	launch_box(box, i, data);
	freedata(data);
	return ;
}

void	minishell(t_data *data, char **env)
{
	int		err;

	take_start_env(data, env);
	increment_shlvl(data);
	while (1)
	{
		err = errno;
		if (!data->env)
			error_mes_with_exit("🔥mini_hell🔥: error environment\n", data);
		data->instr = delete_hashtag(readline("🔥mini_hell🔥$ "));
		errno = err;
		if (!data->instr)
			error_mes_with_exit("\b\bexit\n", data);
		if (data->instr[0] == 0)
		{
			free(data->instr);
			continue ;
		}
		add_history(data->instr);
		pars_and_launch(data, 1);
	}
	delenv(&data->env);
	freedata(data);
}

void	ft_takesig(int sig)
{
	if (sig == SIGINT)
	{
		errno = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_data				data;

	if (check_argv(argc, argv, env, &data))
		return (1);
	signal(SIGINT, ft_takesig);
	signal(SIGQUIT, SIG_IGN);
	minishell(&data, env);
	return (0);
}
