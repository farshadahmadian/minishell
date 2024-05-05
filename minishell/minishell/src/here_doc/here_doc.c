/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:19:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/13 11:24:47 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	perform_here_doc(t_redir_data *redir_cont, t_data *data, char *eof)
{
	int		fd_tmp;

	fd_tmp = open(redir_cont->f_name, O_WRONLY);
	if (fd_tmp == -1)
		return (error("here_doc", NULL, errno), 1);
	if (get_interactive_input(fd_tmp, &eof, data))
	{
		close(fd_tmp);
		return (error("here_doc", NULL, errno), 1);
	}
	close(fd_tmp);
	return (0);
}

static int	check_redir(t_list *redir, t_data *data, char **eofs, int *i)
{
	t_redir_data	*redir_cont;

	if (!redir)
		return (0);
	while (redir)
	{
		redir_cont = (t_redir_data *)redir->content;
		if (redir_cont->type == REDIR_HERE_DOC)
		{
			if (perform_here_doc(redir_cont, data, eofs[*i]))
			{
				data->e_code = 1;
				return (1);
			}
			(*i)++;
		}
		redir = redir->next;
	}
	return (0);
}

static int	child_here_doc(t_node *tree, t_data *data, char **eofs)
{
	t_pipe	*pipe;
	t_cmd	*cmd;
	int		i;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		if (check_redir(cmd->redir, data, eofs, &i))
			return (free_dptr(eofs), 1);
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	if (check_redir(cmd->redir, data, eofs, &i))
		return (free_dptr(eofs), 1);
	return (free_dptr(eofs), 0);
}

static int	resolve_here_doc(t_node *tree, t_data *data, char **eofs)
{
	int		pid_hd;
	int		wstatus;

	wstatus = 0;
	pid_hd = fork();
	if (pid_hd == -1)
		return (error("fork", NULL, errno), 1);
	if (pid_hd == 0)
	{
		if (child_here_doc(tree, data, eofs))
			free_child_and_exit(data, NULL, 1);
		free_child_and_exit(data, NULL, 0);
	}
	waitpid(pid_hd, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (1);
	return (0);
}

int	here_doc(t_node *tree, t_data *data)
{
	char	**eofs;

	if (!data->tree)
		return (1);
	eofs = collect_eofs(tree, data);
	if (!eofs)
		return (0);
	signal(SIGINT, SIG_IGN);
	data->e_code = resolve_here_doc(tree, data, eofs);
	free_dptr(eofs);
	return (data->e_code);
}
