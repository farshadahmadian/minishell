/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:26:16 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 14:19:29 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (kind_of_quotes == -1)
// 	kind_of_quotes = s[i];
// else if (kind_of_quotes == s[i])
// 	kind_of_quotes = -1;
// else
// {
// 	new_str[j] = s[i];
// 	j++;
// }

static void	handle_quotes_and_cpy(char *quotes, char *new_str, char c, int *j)
{
	if (*quotes == -1)
		*quotes = c;
	else if (*quotes == c)
		*quotes = -1;
	else
	{
		new_str[*j] = c;
		(*j)++;
	}
}

static char	*copy_without_quotes(char *s, int len)
{
	char	*new_str;
	int		i;
	int		j;
	char	kind_of_quotes;

	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	new_str[len] = '\0';
	i = 0;
	j = 0;
	kind_of_quotes = -1;
	while (s[i])
	{
		if (s[i] == TKN_S_QUOTE || s[i] == TKN_D_QUOTE)
			handle_quotes_and_cpy(&kind_of_quotes, new_str, s[i], &j);
		else
		{
			new_str[j] = s[i];
			j++;
		}
		i++;
	}
	return (new_str);
}

static int	get_len_without_quotes(char *s)
{
	int		i;
	int		len;
	char	kind_of_quotes;

	i = 0;
	len = 0;
	kind_of_quotes = -1;
	while (s[i])
	{
		if (s[i] == TKN_S_QUOTE || s[i] == TKN_D_QUOTE)
		{
			if (kind_of_quotes == -1)
				kind_of_quotes = s[i];
			else if (kind_of_quotes == s[i])
				kind_of_quotes = -1;
			else
				len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*remove_quote_pairs(char *s)
{
	int		new_len;
	char	*new_str;

	new_len = get_len_without_quotes(s);
	new_str = copy_without_quotes(s, new_len);
	return (new_str);
}
