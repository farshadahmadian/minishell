/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_dptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:49:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 12:43:53 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Counts the number of variables whose value is not NULL.
*/
int	get_exported_var_n(t_list *env)
{
	t_var	*var;
	int		n;

	n = 0;
	while (env)
	{
		var = (t_var *)env->content;
		if (var->value)
			n++;
		env = env->next;
	}
	return (n);
}

static char	*prepare_var(char *name, char *value)
{
	char	*joined;
	char	*tmp;

	joined = ft_strjoin(name, "=");
	if (!joined)
		return (NULL);
	tmp = joined;
	joined = ft_strjoin(joined, value);
	if (!joined)
		return (free(tmp), NULL);
	free(tmp);
	return (joined);
}

/*
	Convert the t_list to char **, whose format is needed by the execve().
*/
char	**convert_to_dptr(t_list *env)
{
	char	**new_env;
	t_var	*var;
	int		n;
	int		i;
	char	*joined;

	n = get_exported_var_n(env);
	new_env = ft_calloc(n + 1, sizeof(char *));
	if (!new_env)
		return (error("convert env to dptr", NULL, errno), NULL);
	new_env[n] = NULL;
	i = 0;
	while (env)
	{
		var = (t_var *)env->content;
		if (var->value)
		{
			joined = prepare_var(var->name, var->value);
			if (!joined)
				return (free_dptr(new_env), NULL);
			new_env[i++] = joined;
		}
		env = env->next;
	}
	return (new_env);
}
