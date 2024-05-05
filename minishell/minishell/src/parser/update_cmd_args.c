/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:01:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 10:51:23 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_args(char *arg, t_cmd *cmd)
{
	cmd->args = ft_calloc(2, sizeof(char *));
	if (!cmd->args)
		return (1);
	cmd->args[0] = ft_strdup(arg);
	if (!cmd->args[0])
		return (1);
	cmd->args[1] = NULL;
	return (0);
}

static int	count_n_args(t_cmd *cmd)
{
	int	n_args;

	n_args = 0;
	while (cmd->args[n_args])
		n_args++;
	return (n_args);
}

/*
	Update char **args inside t_cmd. If the recieved arg is the first, a
	cmd->args is allocated for the first time. If cmd->args already exists,
	it is updated with the new arg.
*/
int	update_cmd_args(char *arg, t_cmd *cmd)
{
	int		i;
	int		n_args;
	char	**new_args;

	if (!cmd->args)
		return (init_args(arg, cmd));
	n_args = count_n_args(cmd);
	new_args = ft_calloc(n_args + 2, sizeof(char *));
	if (!new_args)
		return (1);
	i = 0;
	while (i < n_args)
	{
		new_args[i] = ft_strdup(cmd->args[i]);
		if (!new_args[i])
			return (1);
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
		return (1);
	new_args[i + 1] = NULL;
	free_dptr(cmd->args);
	cmd->args = new_args;
	return (0);
}
