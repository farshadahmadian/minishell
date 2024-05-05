/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:16 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 16:53:12 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_wstatus(int *wstatus)
{
	if (WIFEXITED(*wstatus))
		return (WEXITSTATUS(*wstatus));
	if (WIFSIGNALED(*wstatus))
		return (WTERMSIG(*wstatus) + 128);
	return (0);
}

static int	wait_children(pid_t *ps_id, int n_cmd, int *wstatus)
{
	int		last_e_code;
	pid_t	w_pid;
	int		i;

	last_e_code = 0;
	i = 0;
	while (i < n_cmd)
	{
		w_pid = waitpid(ps_id[i], wstatus, 0);
		if (w_pid == -1)
			return (error("waitpid", NULL, errno), 1);
		if (w_pid == ps_id[i])
			last_e_code = check_wstatus(wstatus);
		i++;
	}
	return (last_e_code);
}

static void	iter_redirections(t_list *redir)
{
	t_list			*head;
	t_redir_data	*content;

	head = redir;
	while (head)
	{
		content = (t_redir_data *)head->content;
		if (content->type == REDIR_HERE_DOC)
			unlink(content->f_name);
		head = head->next;
	}
}

void	unlink_here_doc(t_node *tree)
{
	t_node	*node;
	t_pipe	*pipe;
	t_cmd	*cmd;

	node = tree;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		cmd = (t_cmd *)pipe->left->content;
		iter_redirections(cmd->redir);
		node = pipe->right;
	}
	cmd = (t_cmd *)node->content;
	iter_redirections(cmd->redir);
}

int	parent(t_data *data)
{
	int	wstatus;

	wstatus = 0;
	if (data->pid)
		data->e_code = wait_children(data->pid, data->n_ps, &wstatus);
	unlink_here_doc(data->tree);
	return (0);
}
