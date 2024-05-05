/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:08:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 10:42:42 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The function is a state changer for the quotes, so that is possible to
	understand where the expansion has to be performed.
*/
void	change_is_open_quote(char curr_quote, char *is_open)
{
	if (*is_open == -1)
		(*is_open) = curr_quote;
	else
	{
		if ((*is_open) == curr_quote)
			(*is_open) = -1;
	}
}

static char	*copy_without_translation_operator(char *old, int len)
{
	int		i;
	int		j;
	char	is_open;
	char	*mid_str;

	mid_str = ft_calloc(len + 1, sizeof(char));
	if (!mid_str)
		return (NULL);
	mid_str[len] = '\0';
	is_open = -1;
	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] == '$' && is_open == -1)
			if (old[i + 1] == '\'' || old[i + 1] == '\"')
				i++;
		if (old[i] == '\'' || old[i] == '\"')
			change_is_open_quote(old[i], &is_open);
		mid_str[j] = old[i];
		j++;
		i++;
	}
	return (mid_str);
}

static size_t	get_len_without_translation_operator(char *old)
{
	size_t	len;
	int		i;
	char	is_open;

	is_open = -1;
	len = 0;
	i = 0;
	while (old[i])
	{
		if (old[i] == '$' && (old[i + 1] == '\'' || old[i + 1] == '\"'))
		{
			if (is_open == -1)
				i++;
			else
			{
				len++;
				i++;
			}
		}
		if (old[i] == '\'' || old[i] == '\"')
			change_is_open_quote(old[i], &is_open);
		len++;
		i++;
	}
	return (len);
}

/*
	$"..." and $'...' are called translation operators. In this mid step of
	expansion, all translation operators $ are removed to make the next steps
	of expansion easier to handle. The quotes are removed in the steps later.
*/
char	*remove_translation_operator(char *old_str)
{
	size_t	new_len;
	char	*mid_str;

	mid_str = NULL;
	new_len = get_len_without_translation_operator(old_str);
	if (ft_strlen(old_str) == new_len)
		mid_str = ft_strdup(old_str);
	else
		mid_str = copy_without_translation_operator(old_str, new_len);
	return (mid_str);
}
