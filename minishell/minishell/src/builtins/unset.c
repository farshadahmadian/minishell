/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:37:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/13 11:29:32 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_head(t_list *head, t_list **env, char *name)
{
	t_var	*var;
	t_list	*tmp;

	var = NULL;
	tmp = NULL;
	if (head == (*env))
	{
		var = (t_var *)head->content;
		if (ft_strcmp(var->name, name) == 0)
		{
			tmp = (*env)->next;
			ft_lstdelone(head, del_var_content);
			(*env) = tmp;
			return (1);
		}
	}
	return (0);
}

static int	unset_mid_last(t_list *head, char *name)
{
	t_list	*next_node;

	next_node = NULL;
	if (head->next)
	{
		next_node = (t_list *)head->next;
		if (ft_strcmp(((t_var *)next_node->content)->name, name) == 0)
		{
			head->next = next_node->next;
			ft_lstdelone(next_node, del_var_content);
			return (1);
		}
	}
	return (0);
}

static void	unset_single_var(char *name, t_list **env)
{
	t_list	*head;

	head = (*env);
	while (head)
	{
		if (unset_head(head, env, name))
			break ;
		if (unset_mid_last(head, name))
			break ;
		head = head->next;
	}
}

static int	is_valid_unset_identifier(char *arg)
{
	int		i;

	i = 0;
	if (ft_strchr(arg, '='))
		return (error("unset", arg, CE_INVALIDIDENTIFIER), 0);
	if (ft_isdigit(arg[0]))
		return (error("unset", arg, CE_INVALIDIDENTIFIER), 0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (error("unset", arg, CE_INVALIDIDENTIFIER), 0);
		i++;
	}
	return (1);
}

/*
	The environment variable specified by <name> is unset for the current
	environment. If the argument is a variable which doesn't exist, nothing
	happens. If there are invalid identifiers, the function doesn't returns,
	and the other arguments are processed.
*/
int	unset(t_cmd *cmd, t_data *data)
{
	int		i;

	if (!cmd->args[1])
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_unset_identifier(cmd->args[i]))
			unset_single_var(cmd->args[i], &data->env);
		i++;
	}
	return (0);
}
