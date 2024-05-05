/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:31:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/13 11:00:48 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_n_cmds(t_node *node)
{
	t_pipe	*pipe;
	int		n;

	n = 0;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		n += 1;
		node = pipe->right;
	}
	n += 1;
	return (n);
}

/*
	signal() ignores the init_sig_handling(), which sets the global to 1.
	This is needed to catch the exit code of such programs like cat and sleep.
*/
void	executor(t_data *data)
{
	if (!data->tree)
		return ;
	signal(SIGINT, SIG_IGN);
	data->n_ps = get_n_cmds(data->tree);
	if (data->tree->type == IS_CMD)
	{
		if (execute_single_cmd(data))
		{
			parent(data);
			return ;
		}
	}
	else
	{
		if (execute_pipechain(data))
		{
			parent(data);
			data->e_code = 1;
			return ;
		}
	}
	parent(data);
}
