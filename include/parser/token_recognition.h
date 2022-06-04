/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:08:40 by hseong            #+#    #+#             */
/*   Updated: 2022/06/04 23:19:34 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_RECOGNITION_H
# define TOKEN_RECOGNITION_H

# define TABLE_SIZE (8)
# define CONTINUE (0)
# define DELIMIT (1)
# define APPLIED (2)

typedef int	(*t_token_recog_func)(t_iterator *, t_token *);

int	check_eoi(t_iterator *iterator, t_token *token);
int	check_operator(t_iterator *iterator, t_token *token);
int	check_quote(t_iterator *iterator, t_token *token);
int	check_dollar(t_iterator *iterator, t_token *token);
int	check_new_operator(t_iterator *iterator, t_token *token);
int	check_blank(t_iterator *iterator, t_token *token);
int	check_word(t_iterator *iterator, t_token *token);
int	check_new_word(t_iterator *iterator, t_token *token);

static const t_token_recog_func	g_token_recog_tab[8]
	= {
	check_eoi,
	check_operator,
	check_quote,
	check_dollar,
	check_new_operator,
	check_blank,
	check_word,
	check_new_word
};

int		expand_operator(char target, int type);
void	find_expansion_word(t_iterator *iterator, t_token *token);
int		is_operator(char target);
int		is_special(char target);

#endif