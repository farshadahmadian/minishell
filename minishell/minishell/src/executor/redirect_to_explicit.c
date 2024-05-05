/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_to_explicit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:43:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/10 11:34:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	duplicate_fd(int fd_in, int fd_out)
{
	if (fd_in != -2)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(fd_in);
	}
	if (fd_out != -2)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(fd_out);
	}
	return (0);
}

static int	open_flag_mode(char *f_name, int *last_fd, int flags, int mode)
{
	int	fd;

	fd = -2;
	if (*last_fd >= 0)
		close(*last_fd);
	fd = open(f_name, flags, mode);
	if (fd == -1)
		return (error(f_name, NULL, errno), -1);
	return (fd);
}

/*
	Based on the current redirection, certain flags and modes for the open()
	function are set. In the first case, no mode is required, so 0 is passed.
*/
static int	is_valid_fd(t_redir_data *redir, int *fd_in, int *fd_out)
{
	int	flags;

	flags = -1;
	if (redir->type == REDIR_IN || redir->type == REDIR_HERE_DOC)
	{
		flags = O_RDONLY;
		*fd_in = open_flag_mode(redir->f_name, fd_in, flags, 0);
		return (*fd_in);
	}
	else if (redir->type == REDIR_OUT)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		*fd_out = open_flag_mode(redir->f_name, fd_out, flags, 0644);
		return (*fd_out);
	}
	else if (redir->type == REDIR_APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		*fd_out = open_flag_mode(redir->f_name, fd_out, flags, 0644);
		return (*fd_out);
	}
	return (-2);
}

/*
	get_last_redir returns (-1) in case of open() error and (0) in case of
	success. The function has to stop as soon as an error occurs. The
	last redirection in the list, are the one which are performed, and
	are stored into *fd_in and *fd_out.
*/
static int	get_last_redir(t_cmd *cmd, int *fd_in, int *fd_out)
{
	t_list			*head;
	t_redir_data	*redir_cont;
	int				last_fd;

	last_fd = -2;
	head = cmd->redir;
	while (head)
	{
		redir_cont = (t_redir_data *)head->content;
		last_fd = is_valid_fd(redir_cont, fd_in, fd_out);
		if (last_fd == -1)
			return (-1);
		head = head->next;
	}
	return (0);
}

/*
	Attempt to perform each redirection int and out. If an error is found,
	the operation is immediately stopped, otherwise dup2() is peformed.
*/
int	redirect_to_explicit(t_node *node)
{
	t_cmd	*cmd;
	int		fd_err;
	int		fd_in;
	int		fd_out;

	fd_in = -2;
	fd_out = -2;
	fd_err = 0;
	cmd = (t_cmd *)node->content;
	if (cmd->redir)
	{
		if (get_last_redir(cmd, &fd_in, &fd_out) == -1)
			return (1);
		else
			fd_err = duplicate_fd(fd_in, fd_out);
	}
	if (fd_err == -1)
		return (error("dup2", NULL, errno), 1);
	return (0);
}

// #include "minishell.h"

// static int	open_flag_mode(char *f_name, int last_fd, int flags, int mode)
// {
// 	int fd;

// 	fd = -2;
// 	if (last_fd >= 0)
// 		close(last_fd);
// 	fd = open(f_name, flags, mode);
// 	if (fd == -1)
// 		return (error(f_name, NULL, errno), -1);
// 	return (fd);
// }

// static int	is_valid_fd(t_cmd *cmd, t_redir_data *redir)
// {
// 	int	flags;

// 	flags = -1;
// 	if (redir->type == REDIR_IN || redir->type == REDIR_HERE_DOC)
// 	{
// 		flags = O_RDONLY;
// 		cmd->fd_in = open_flag_mode(redir->f_name, cmd->fd_in, flags, 0);
// 		return (cmd->fd_in); // 0 mode is ignored
// 	}
// 	else if (redir->type == REDIR_OUT)
// 	{
// 		flags = O_WRONLY | O_CREAT | O_TRUNC;
// 		cmd->fd_out = open_flag_mode(redir->f_name, cmd->fd_out, flags, 0644);
// 		return (cmd->fd_out);
// 	}
// 	else if (redir->type == REDIR_APPEND)
// 	{
// 		flags = O_WRONLY | O_CREAT | O_APPEND;
// 		cmd->fd_out = open_flag_mode(redir->f_name, cmd->fd_out, flags, 0644);
// 		return (cmd->fd_out);
// 	}
// 	return (-2);
// }

// /*
// 	get_last_redir returns (0) in case of open() error and (1) in case of
// 	success. The function has to stop as soon as an error occurs. The
// 	last redirection in the list, are the one which are performed, and
// 	are stored into cmd->fd_in and cmd->fd_out.
// */
// static int	get_last_redir(t_cmd *cmd)
// {
// 	t_list			*head;
// 	t_redir_data	*redir_cont;
// 	int				last_fd;

// 	last_fd = -2;
// 	head = cmd->redir;
// 	while (head)
// 	{
// 		redir_cont = (t_redir_data *)head->content;
// 		last_fd = is_valid_fd(cmd, redir_cont);
// 		if (last_fd == -1)
// 			return (-1);
// 		head = head->next;
// 	}
// 	return (0);
// }

// int	redirect_to_explicit(t_node *node)
// {
// 	t_cmd	*cmd;
// 	int		fd_ret;

// 	/*
// 		IDEA - remove fd_in and fd_out in t_cmd
// 		and create them in THIS function.
// 	*/
// 	cmd = (t_cmd *)node->content;
// 	fd_ret = 0;
// 	if (cmd->redir)
// 	{
// 		if (get_last_redir(cmd) == -1) // error
// 			return (1);
// 		else
// 		{
// 			if (cmd->fd_in != -2)
// 			{
// 				fd_ret = dup2(cmd->fd_in, STDIN_FILENO);
// 				close(cmd->fd_in);
// 			}
// 			if (cmd->fd_out != -2)
// 			{
// 				fd_ret = dup2(cmd->fd_out, STDOUT_FILENO);
// 				close(cmd->fd_out);
// 			}
// 		}
// 	}
// 	if (fd_ret == -1)
// 		return (error("dup2", NULL, errno), 1);
// 	return (0);
// }
