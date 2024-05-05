/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:05:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 14:48:05 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	get_abs_path() returns 3 kinds of value: (1) in case no command was found
	inside $PATH; (0) in case of a command was found; (-1) in case of malloc
	errors.
*/
static int	get_abs_path(char *cmd_name, char **abs_path, char **env)
{
	char	*path_var;
	char	**paths;
	int		i;
	int		ret_value;

	ret_value = 0;
	path_var = get_path_var(env);
	if (!path_var)
		return (1);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (1);
	i = 0;
	while (paths[i])
	{
		ret_value = file_and_exec_ok(cmd_name, abs_path, paths[i]);
		if (ret_value == -1)
			return (free_dptr(paths), -1);
		if (ret_value == 0)
			return (free_dptr(paths), 0);
		i++;
	}
	return (free_dptr(paths), 1);
}

/*
	If the cmd_name contains a path, the function verifies if it is a directory
	(/bin) and in that case return (126). If it contains a path but it's not a
	directory (/bin/ls), it verifies F_OK and X_OK, returning (127) in case of
	error (in this case, execve() is not called.
	If cmd_name doesn't contain a path, it is built using the $PATH variable.
	(-1) is returned in case of error, (0) in case of an abs_path is built
	successfully, (1) in case nothing is found.
*/
int	resolve_cmd_path(char **cmd_name, char **env)
{
	char	*abs_path;
	char	*tmp;
	int		ret_value;

	abs_path = NULL;
	if (contains_a_path(*cmd_name))
	{
		if (is_a_directory(*cmd_name))
			return (error(*cmd_name, NULL, 126), 126);
		if (access(*cmd_name, F_OK | X_OK) == 0)
			return (0);
		return (error(*cmd_name, NULL, errno), 127);
	}
	ret_value = get_abs_path(*cmd_name, &abs_path, env);
	if (ret_value == -1)
		return (-1);
	if (ret_value == 1)
		return (1);
	tmp = *cmd_name;
	*cmd_name = abs_path;
	free(tmp);
	return (0);
}
