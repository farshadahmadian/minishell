/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:50:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 13:48:40 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	oldpwd_exists(t_list *env_cpy)
{
	t_list	*head;
	t_var	*var;

	head = env_cpy;
	while (head)
	{
		var = (t_var *)head->content;
		if (ft_strcmp(var->name, "OLDPWD") == 0)
		{
			free(var->value);
			var->value = NULL;
			var->value_len = -1;
			return (1);
		}
		head = head->next;
	}
	return (0);
}

static int	create_oldpwd(t_list *env_cpy)
{
	t_list	*new_node;
	t_var	*new_content;

	new_node = NULL;
	if (!oldpwd_exists(env_cpy))
	{
		new_content = create_var_content("OLDPWD");
		if (!new_content)
			return (1);
		new_node = ft_lstnew(new_content);
		if (!new_node)
			return (del_var_content(new_content), 1);
		ft_lstadd_back(&env_cpy, new_node);
	}
	return (0);
}

static int	increment_shlvl(t_list *env)
{
	t_list	*head;
	t_var	*var;
	int		shlvl;

	head = env;
	while (head)
	{
		var = (t_var *)head->content;
		if (ft_strcmp(var->name, "SHLVL") == 0)
		{
			shlvl = ft_atoi(var->value) + 1;
			free(var->value);
			var->value = ft_itoa(shlvl);
			if (!var->value)
				return (1);
		}
		head = head->next;
	}
	return (0);
}

static int	handle_exceptions(t_list *env)
{
	if (create_oldpwd(env))
		return (1);
	if (increment_shlvl(env))
		return (1);
	return (0);
}

/*
	Copies the environment variable of the parent process into a double
	linked list, to be used in the current shell.
*/
t_list	*init_env(char **env)
{
	t_list	*env_cpy;
	t_list	*new_node;
	t_var	*new_content;
	int		i;

	env_cpy = NULL;
	new_node = NULL;
	i = 0;
	if (!env[i])
		return (create_essential_env());
	while (env[i])
	{
		new_content = create_var_content(env[i]);
		if (!new_content)
			return (ft_lstclear(&env_cpy, del_var_content), NULL);
		new_node = ft_lstnew(new_content);
		if (!new_node)
			return (ft_lstclear(&env_cpy, del_var_content), NULL);
		ft_lstadd_back(&env_cpy, new_node);
		i++;
	}
	if (handle_exceptions(env_cpy))
		return (ft_lstclear(&env_cpy, del_var_content), NULL);
	return (env_cpy);
}
