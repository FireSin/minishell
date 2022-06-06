/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:05:55 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:05:56 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	varisdigit(char **s)
{
	if (ft_isdigit(**s))
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int	writevar(char **str, t_envr p)
{
	char	*tmp;

	if (*str)
	{
		tmp = *str;
		*str = ft_strjoin(tmp, p.val);
		free(tmp);
	}
	else
		*str = ft_strdup(p.val);
	if (!(*str))
		return (1);
	return (0);
}

int	last_error(char **s, char **str)
{
	char	*tmp;
	char	*err;

	(*s)++;
	err = ft_itoa(errno);
	if (!err)
		return (1);
	if (*str)
	{
		tmp = *str;
		*str = ft_strjoin(tmp, err);
		free(tmp);
	}
	else
		*str = ft_strdup(err);
	free(err);
	if (!(*str))
		return (1);
	return (0);
}
