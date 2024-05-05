/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pipechain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:49:46 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 18:07:42 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**convert_env(t_data *data)
{
	char	**env;

	env = convert_to_dptr(data->env);
	if (!env)
		free_child_and_exit(data, env, 1);
	return (env);
}

static int	redirect(t_node *node, int *pipe, int *prev_pipe)
{
	if (redirect_to_pipes(pipe, prev_pipe))
		return (1);
	if (redirect_to_explicit(node))
		return (1);
	return (0);
}

static int	execute(t_data *data, t_node *node, char **env)
{
	t_cmd	*cmd;
	int		ret_value;

	ret_value = 0;
	cmd = (t_cmd *)node->content;
	if (is_builtin(cmd))
	{
		ret_value = call_builtin_function(cmd, data);
		free_child_and_exit(data, env, ret_value);
	}
	if (cmd->args)
	{
		ret_value = resolve_cmd_path(&cmd->args[0], env);
		if (ret_value == 126 || ret_value == 127 || ret_value == -1)
			free_child_and_exit(data, env, ret_value);
		if (execve(cmd->args[0], cmd->args, env))
		{
			error(cmd->args[0], NULL, CE_CMDNOTFOUND);
			free_child_and_exit(data, env, 127);
		}
	}
	return (0);
}

/*
	In order:
		• char **env is prepared to be sent to execve()
		• stdin and stdout are redirected to pipe ends
		• stdin and stdout are redirected to redir (< << >> >)
		• if builtin, it's run separately with proper functions (no execve());
		• if normal cmd, execve() is called
*/
void	child_pipechain(t_data *data, t_node *node, int *pipe, int *prev_pipe)
{
	char	**env;
	int		ret_value;

	ret_value = 0;
	env = convert_env(data);
	if (redirect(node, pipe, prev_pipe))
		free_child_and_exit(data, env, ret_value);
	if (!execute(data, node, env))
		free_child_and_exit(data, env, 0);
}
