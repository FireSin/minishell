/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listwork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:19 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:20 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	take_data_in_list(t_comm **temp, t_data *data, int i)
{
	(*temp)->comm = NULL;
	(*temp)->oper = NULL;
	(*temp)->data = data;
	(*temp)->next = NULL;
	(*temp)->prev = NULL;
	(*temp)->fd[0] = 0;
	(*temp)->fd[1] = 0;
	(*temp)->status = 0;
	(*temp)->prnt = i;
	(*temp)->args = malloc(sizeof(char *) * 3);
	if (!(*temp)->args)
		return ;
	(*temp)->args[0] = ft_strdup("./🔥mini_hell🔥");
	if (!(*temp)->args[0])
		return ;
	(*temp)->args[1] = NULL;
	(*temp)->args[2] = NULL;
}

t_comm	*addelem(t_data *data, int i)
{
	t_comm	*temp;
	t_comm	*p;

	temp = (t_comm *)malloc(sizeof(t_comm));
	if (!temp)
		return (NULL);
	take_data_in_list(&temp, data, i);
	if (!temp->args || !temp->args[0])
		return (NULL);
	if (!data->comm)
	{
		data->comm = temp;
		temp->i = 0;
		return (temp);
	}
	p = data->comm;
	while (p->next)
		p = p->next;
	p->next = temp;
	temp->prev = p;
	temp->i = p->i + 1;
	return (temp);
}

void	delcommand(t_comm **comm)
{
	int		i;
	t_comm	*p;

	while (*comm)
	{
		i = 0;
		p = *comm;
		*comm = p->next;
		while (p->args && p->args[i])
		{
			free(p->args[i]);
			p->args[i++] = NULL;
		}
		free(p->args);
		if (p->comm)
			free(p->comm);
		if (p->oper)
			free(p->oper);
		free(p);
	}
}

void	delenv(t_envr **env)
{
	t_envr	*p;

	while (*env)
	{
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->val)
			free((*env)->val);
		p = *env;
		*env = (*env)->next;
		free (p);
	}
}
