/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:17:07 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 17:34:36 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	@param n: number of charachter to compare. It is needed to differentiate
	between var+=value which append value to the var, and var=value, which
	assigns it truncating the already existing content.
*/
static int	env_var_exist(char *tmp_var_name, t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strcmp(var->name, tmp_var_name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

static int	append_to_existing_var(t_var *var, char *new_value)
{
	char	*tmp;

	tmp = var->value;
	var->value = ft_strjoin(var->value, new_value);
	if (!var->value)
		return (1);
	free(tmp);
	return (0);
}

static int	update_var(char *name, char *new_value, t_list *env, int to_append)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strcmp(var->name, name) == 0)
		{
			if (to_append)
			{
				if (append_to_existing_var(var, new_value))
					return (1);
				break ;
			}
			else
			{
				free(var->value);
				var->value = ft_strdup(new_value);
				if (!var->value)
					return (1);
				break ;
			}
		}
		env = env->next;
	}
	return (0);
}

static void	cut_append_sign(t_var *var, int *to_append)
{
	char	*tmp;

	if (var->name[var->name_len - 1] != '+')
		return ;
	*to_append = 1;
	tmp = var->name;
	var->name = ft_substr(var->name, 0, var->name_len - 1);
	free(tmp);
}

/*
	Exports the specified variable to the subshells and child processes.
	• IF the var doesn't exist yet, a new one is created and added to the env
	• IF the var exist, if arg is initialized (at least = sign at the end),
		the variable need to be replaced. If at the left ofthe equal sign there
		is a + , than the old value is not replaces, but the new one is
		appended.
*/
int	check_export(char *arg, t_list **env)
{
	t_var	*tmp_var;
	t_list	*new_node;
	int		to_append;

	to_append = 0;
	new_node = NULL;
	tmp_var = create_var_content(arg);
	cut_append_sign(tmp_var, &to_append);
	if (!tmp_var->name)
		return (del_var_content(tmp_var), 1);
	if (!env_var_exist(tmp_var->name, *env))
	{
		new_node = ft_lstnew(tmp_var);
		if (!new_node)
			return (1);
		ft_lstadd_back(env, new_node);
		return (0);
	}
	if (tmp_var->value)
	{
		if (update_var(tmp_var->name, tmp_var->value, *env, to_append))
			return (del_var_content(tmp_var), 1);
	}
	del_var_content(tmp_var);
	return (0);
}
