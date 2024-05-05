/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:44:50 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/12 14:34:21 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define SPECIAL_CHAR_NUM 10

typedef enum e_tkn_type
{
	TKN_WORD = 1,
	TKN_S_QUOTED_STR = 2,
	TKN_D_QUOTED_STR = 3,
	TKN_NOT_CLOSED_S_QUOTE_STR = 4,
	TKN_NOT_CLOSED_D_QUOTE_STR = 5,
	TKN_ENV_VAR = 6,
	TKN_REDIR_APPEND = 7,
	TKN_HERE_DOC = 8,
	TKN_REDIR_IN = '<',
	TKN_REDIR_OUT = '>',
	TKN_SPACE_CAHR = ' ',
	TKN_TAB_CHAR = '\t',
	TKN_NEW_LINE = '\n',
	TKN_S_QUOTE = '\'',
	TKN_D_QUOTE = '"',
	TKN_ESCAPE_CHAR = '\\',
	TKN_PIPE = '|',
	TKN_DOLLAR_CHAR = '$',
}	t_tkn_type;

typedef enum s_quote
{
	NOT_QUOTED = 1,
	IN_S_QUOTE,
	IN_D_QUOTE,
}	t_quote;

typedef enum s_quote_status
{
	NO_QUOTE = -1,
	CLOSED_QUOTE = 0,
	OPEN_QUOTE = 1,
	OPEN_AND_CLOSED_PAIRS = 2,
}	t_quote_status;

typedef enum s_white_space
{
	INIT_WHITE_SPACE = -1,
	NOT_FOLLOWED_BY_WHITE_SPACE = 0,
	FOLLOWED_BY_WHITE_SPACE = 1,
}	t_white_space;

typedef struct s_quote_open
{
	bool	is_s_quote_open;
	bool	is_d_quote_open;
}	t_quote_open;

typedef struct s_tkn_data
{
	char			*str;
	t_tkn_type		type;
	t_white_space	white_space;
	int				str_len;
	int				list_size;
	t_quote			quote;
	t_quote_status	quote_status;
}	t_tkn_data;

void			lexer(char *input, t_list **tkns_head);
void			tokenize_input(char *input, t_list **tkn_head);
char			*store_special_char_as_tkn(char *c, t_list **tkn_head);
char			*store_prev_chars_as_tkn(char *ref, int tkn_counter,
					t_list **tkn_head);
void			read_char(char cur_char, char **ref, int *tkn_ctr,
					t_list **tkn_head);
void			check_each_tkn_str(t_tkn_data *tkn_data);
t_quote_open	*detect_quote(t_tkn_data *tkn_data, char tkn_first_char,
					t_quote *position);
void			assign_type_to_tkn(t_list *tkns_head);
void			assign_quote_status_to_tkn(t_list *tkns_head);
void			merge_consecutive_less_or_greater_than(t_list *tkns_head);
void			delete_not_quoted_spaces(t_list **tkns_head);
void			merge_dollar_char_with_next_token(t_list *tkns_head);
void			merge_quoted_tokens(t_list *tkns_head);
void			del_tokens(void *content);
void			assign_following_space_status(t_list *tkns_head);
char			*join_two_strs(char **cur_str, char *next_str);
void			remove_next_node(t_list *cur_node);
void			merge_strings(t_list *tkn);
void			print_tokens(t_list *tokens);

#endif
