/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:18:14 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/13 08:04:43 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_to_lowcase(char *s)
{
	char	*s_lowcase;
	int		i;

	s_lowcase = ft_strdup(s);
	if (!s_lowcase)
		return (NULL);
	i = 0;
	while (s[i])
	{
		s_lowcase[i] = ft_tolower(s[i]);
		i++;
	}
	s_lowcase[i] = '\0';
	return (s_lowcase);
}

int	is_builtin(t_cmd *cmd)
{
	char	*cmd_low;

	if (!cmd->args)
		return (0);
	cmd_low = str_to_lowcase(cmd->args[0]);
	if (!cmd_low)
		return (free(cmd_low), 1);
	if (ft_strcmp(cmd_low, "cd") == 0)
		return (free(cmd_low), 1);
	if (ft_strcmp(cmd_low, "echo") == 0)
		return (free(cmd_low), 1);
	if (ft_strcmp(cmd_low, "exit") == 0)
		return (free(cmd_low), 1);
	if (ft_strcmp(cmd_low, "export") == 0)
		return (free(cmd_low), 1);
	if (ft_strcmp(cmd_low, "env") == 0)
		return (free(cmd_low), 1);
	if (ft_strcmp(cmd_low, "pwd") == 0)
		return (free(cmd_low), 1);
	if (ft_strcmp(cmd_low, "unset") == 0)
		return (free(cmd_low), 1);
	return (free(cmd_low), 0);
}

/*
	This function is called for the builtins which are part of a pipeline. They
	have a different function which call the custom functions. Pipes and
	redir are performed before (child() function).
*/
int	call_builtin_function(t_cmd *cmd, t_data *data)
{
	char	*cmd_low;

	if (!cmd->args)
		return (0);
	cmd_low = str_to_lowcase(cmd->args[0]);
	if (!cmd_low)
		return (1);
	if (ft_strcmp(cmd_low, "cd") == 0)
		data->e_code = cd(cmd, data);
	else if (ft_strcmp(cmd_low, "echo") == 0)
		data->e_code = echo(data, cmd);
	else if (ft_strcmp(cmd_low, "exit") == 0)
		data->e_code = exit_custom(cmd, data);
	else if (ft_strcmp(cmd_low, "export") == 0)
		data->e_code = export(cmd, data);
	else if (ft_strcmp(cmd_low, "env") == 0)
		data->e_code = print_env(data->env);
	else if (ft_strcmp(cmd_low, "pwd") == 0)
		data->e_code = pwd();
	else if (ft_strcmp(cmd_low, "unset") == 0)
		data->e_code = unset(cmd, data);
	free(cmd_low);
	return (data->e_code);
}

/*
	This function is called for the builtins which are NOT part of a pipeline.
	They are not part of a pipeline because of some particular features
	(basic example cd). Since there could be a possible redirection, the
	default stdin and stdout need to be dup() to be restored.
*/
int	run_builtin_same_ps(t_data *data)
{
	t_cmd	*cmd;
	int		def_stdin;
	int		def_stdout;

	def_stdin = dup(STDIN_FILENO);
	def_stdout = dup(STDOUT_FILENO);
	if (def_stdin == -1 || def_stdout == -1)
	{
		data->e_code = 1;
		return (error("builtin", NULL, errno), 1);
	}
	if (redirect_to_explicit(data->tree))
	{
		data->e_code = 1;
		return (data->e_code);
	}
	cmd = (t_cmd *)data->tree->content;
	data->e_code = call_builtin_function(cmd, data);
	if (dup2(def_stdin, STDIN_FILENO) == -1
		|| dup2(def_stdout, STDOUT_FILENO) == -1)
	{
		data->e_code = 1;
		return (error("builtin", NULL, errno), 1);
	}
	return (data->e_code);
}
