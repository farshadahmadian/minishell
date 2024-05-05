/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:09:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 17:30:12 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_exported(t_list *env)
{
	char	**sorted_env;
	bool	is_equal;
	int		i;

	is_equal = false;
	sorted_env = sort_export(env);
	sorted_env = check_next_chars(sorted_env);
	i = 0;
	while (sorted_env[i])
		print_each_line(&i, &is_equal, sorted_env);
	free_dptr(sorted_env);
	return (0);
}

static int	is_valid_export_identifier(char *arg)
{
	int	i;
	int	assigned;

	if (arg[0] == '=' || ft_isdigit(arg[0]))
		return (error("export", arg, CE_INVALIDIDENTIFIER), 0);
	assigned = 0;
	i = 0;
	while (arg[i])
	{
		if (!assigned)
		{
			if (arg[i] == '=')
				assigned = 1;
			else if (arg[i] == '+' && arg[i + 1] == '=')
				return (1);
			else if (!ft_isalnum(arg[i]) && arg[i] != '_')
				return (error("export", arg, CE_INVALIDIDENTIFIER), 0);
		}
		i++;
	}
	return (1);
}

int	export(t_cmd *cmd, t_data *data)
{
	int	i;

	if (!cmd->args[1])
		print_exported(data->env);
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (is_valid_export_identifier(cmd->args[i]))
			{
				if (check_export(cmd->args[i], &data->env))
					return (1);
			}
			i++;
		}
	}
	return (0);
}
