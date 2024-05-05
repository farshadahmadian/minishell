/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipechain.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:08:00 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 13:37:26 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The last child ps call the child() function without fd_pipe, because
	it doesn't need them, since it has to read from the prev_pipe, and write
	to the STDOUT.
*/
static int	fork_last(t_data *data, t_node *node, int *prev_pipe, int i)
{
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		return (error("fork", NULL, errno), 1);
	if (data->pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_pipechain(data, node, NULL, prev_pipe);
	}
	else
		close(*prev_pipe);
	return (0);
}

static int	fork_first_mid(t_data *data, t_node *node, int *prev_pipe, int i)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (error("pipe", NULL, errno), 1);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		return (error("fork", NULL, errno), 1);
	if (data->pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_pipechain(data, node, fd_pipe, prev_pipe);
	}
	else
	{
		close(fd_pipe[1]);
		close(*prev_pipe);
		*prev_pipe = fd_pipe[0];
	}
	return (0);
}

/*
	@param i: the index of the forked process, useful to store in order the
	process id in the main/parent process, to wait for them.
	The function forks the right number of the children, calling a different
	function for the last one.
*/
static int	fork_children(t_data *data, int *prev_pipe)
{
	t_node	*node;
	t_pipe	*pipe;
	int		i;

	node = data->tree;
	i = 0;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		if (fork_first_mid(data, pipe->left, prev_pipe, i))
			return (1);
		node = pipe->right;
		i++;
	}
	if (fork_last(data, node, prev_pipe, i))
		return (1);
	return (0);
}

int	execute_pipechain(t_data *data)
{
	int	prev_pipe;

	data->pid = ft_calloc(data->n_ps, sizeof(int));
	if (!data->pid)
	{
		data->e_code = 1;
		return (error("executor", NULL, errno), 1);
	}
	prev_pipe = dup(STDIN_FILENO);
	if (prev_pipe == -1)
	{
		data->e_code = 1;
		return (error("executor", NULL, errno), 1);
	}
	if (fork_children(data, &prev_pipe))
	{
		data->e_code = 1;
		return (1);
	}
	return (0);
}
