/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_essential_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:08:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 13:48:26 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_var(char *name, t_list **env)
{
	t_list	*new_node;
	t_var	*new_var_cont;

	new_var_cont = create_var_content(name);
	if (!new_var_cont)
		return (1);
	new_node = ft_lstnew(new_var_cont);
	if (!new_node)
		return (del_var_content(new_var_cont), 1);
	if (ft_strcmp(name, "PWD") == 0)
	{
		new_var_cont->value = get_wd();
		if (!new_var_cont->value)
			return (del_var_content(new_var_cont), 1);
		new_var_cont->value_len = ft_strlen(new_var_cont->value);
	}
	if (ft_strcmp(name, "SHLVL") == 0)
	{
		new_var_cont->value = ft_strdup("1");
		if (!new_var_cont->value)
			return (del_var_content(new_var_cont), 1);
		new_var_cont->value_len = 1;
	}
	ft_lstadd_back(env, new_node);
	return (0);
}

/*
	In case the environment is ignored, a minimum and essential environment is
	still created with the following variables.
*/
t_list	*create_essential_env(void)
{
	t_list	*env;

	env = NULL;
	if (add_var("PWD", &env))
		return (ft_lstclear(&env, del_var_content), NULL);
	if (add_var("OLDPWD", &env))
		return (ft_lstclear(&env, del_var_content), NULL);
	if (add_var("SHLVL", &env))
		return (ft_lstclear(&env, del_var_content), NULL);
	return (env);
}
