/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:48:13 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 14:49:46 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_a_path(char *cmd_name)
{
	if (cmd_name[0] == '/')
		return (1);
	if (ft_strncmp(cmd_name, "./", 2) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "../", 3) == 0)
		return (1);
	return (0);
}

int	is_a_directory(char *cmd_name)
{
	struct stat	f_status;

	if (stat(cmd_name, &f_status) == 0 && S_ISDIR(f_status.st_mode))
		return (1);
	return (0);
}

int	file_and_exec_ok(char *cmd_name, char **abs_path, char	*path)
{
	char	*tmp;

	*abs_path = ft_strjoin(path, "/");
	if (!*abs_path)
		return (-1);
	tmp = *abs_path;
	*abs_path = ft_strjoin(*abs_path, cmd_name);
	if (!*abs_path)
		return (free(tmp), -1);
	free(tmp);
	if (access(*abs_path, F_OK | X_OK) == 0 && !is_a_directory(*abs_path))
		return (0);
	free(*abs_path);
	return (1);
}

char	*get_path_var(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}
