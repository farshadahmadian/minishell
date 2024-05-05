/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:38:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 12:58:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	For each variable name in the list, get_env_custom() is applied, and the
	value is duplicated into the node. If the variable doesn't exist, an empty
	string is duplicated.
*/
static void	get_var_values(t_list *var_store, t_list *env, int e_code)
{
	char	*expanded;
	t_var	*var;

	expanded = NULL;
	while (var_store)
	{
		var = (t_var *)var_store->content;
		if (var->name_len == 0)
			expanded = ft_strdup("$");
		else if (var->name[0] == '?' && var->name_len == 1)
			expanded = ft_itoa(e_code);
		else if (get_env_custom(var->name, env))
			expanded = ft_strdup(get_env_custom(var->name, env));
		else
			expanded = ft_strdup("");
		var->value = expanded;
		var->value_len = ft_strlen(var->value);
		var_store = var_store->next;
	}
}

static int	add_node_to_var_store(char *s, t_list **var_store)
{
	t_var	*var;
	t_list	*new_node;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (1);
	var->name_len = get_var_name_len(s);
	if (var->name_len == 0)
		var->name = ft_strdup("$");
	else
		var->name = ft_substr(s, 0, var->name_len);
	if (!var->name)
		return (del_var_content(var), 1);
	var->value = NULL;
	var->value_len = -1;
	new_node = ft_lstnew(var);
	if (!new_node)
		return (del_var_content(var), 1);
	ft_lstadd_back(var_store, new_node);
	return (0);
}

/*
	Creates var_store, a t_list of t_var *, which stores the name of the
	variables that have to be expanded, in the order that they're found.
	Example. "Hello $$USER $HOME world$" results in:
		$ -> USER -> HOME -> $ -> (null)
*/
static t_list	*store_var_names(char *s, int n, char is_open)
{
	t_list	*var_store;
	int		i;

	var_store = NULL;
	i = 0;
	while (i < n)
	{
		while (*s != '$')
		{
			if (*s == TKN_S_QUOTE || *s == TKN_D_QUOTE)
				change_is_open_quote(*s, &is_open);
			s++;
		}
		s++;
		if (is_open == TKN_S_QUOTE)
		{
			i++;
			continue ;
		}
		if (add_node_to_var_store(s, &var_store))
			return (ft_lstclear(&var_store, del_var_content), NULL);
		i++;
	}
	return (var_store);
}

/*
	In order: get n of pssible expansion to perform ("$$$" are still counted
	as three potential expansion to be done), extract the variable names
	("$" is still a variable name), get the variable values and build the
	new string which will replace the origial one.
*/
char	*expand(char *old_str, t_data *data)
{
	int		n;
	t_list	*to_expand;
	char	*mid_str;
	char	*new_str;

	mid_str = remove_translation_operator(old_str);
	if (!mid_str)
		return (NULL);
	n = get_n_dollars(mid_str);
	to_expand = store_var_names(mid_str, n, -1);
	get_var_values(to_expand, data->env, data->e_code);
	new_str = build_str(mid_str, to_expand);
	ft_lstclear(&to_expand, del_var_content);
	free(mid_str);
	return (new_str);
}
