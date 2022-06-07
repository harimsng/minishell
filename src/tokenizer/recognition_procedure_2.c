/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition_procedure_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:28:28 by hseong            #+#    #+#             */
/*   Updated: 2022/06/07 12:51:54 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlinkedlist.h"
#include "libft.h"
#include "constants.h"
#include "parser/token.h"
#include "parser/token_recognition.h"

int	check_new_operator(t_iterator *iterator, t_token *token, char target)
{
	(void)iterator;
	if (!is_operator(target))
		return (CONTINUE);
	if ((token->type & TT_QUOTE_MASK) == TT_QUOTE_MASK)
		return (APPLIED);
	if (token->type != TT_EMPTY)
		return (DELIMIT);
	token->type = get_operator_type(target);
	return (APPLIED);
}

int	check_blank(t_iterator *iterator, t_token *token, char target)
{
	(void)iterator;
	if (!ft_isspace(target))
		return (CONTINUE);
	if ((token->type & TT_QUOTE_MASK) == TT_QUOTE_MASK)
		return (APPLIED);
	return (DELIMIT);
}

int	check_word(t_iterator *iterator, t_token *token, char target)
{
	/*
	char	target;

	target = iterator->line[iterator->end];
	if (is_special(target))
		return (DELIMIT);
	*/
	(void)iterator;
	(void)target;
	if ((token->type & TT_WORD) == TT_WORD)
		return (APPLIED);
	return (CONTINUE);
}

int	check_new_word(t_iterator *iterator, t_token *token, char target)
{
	/*
	char	target;

	target = iterator->line[iterator->end];
	*/
	(void)iterator;
	(void)target;
	token->type = TT_WORD;
	return (APPLIED);
}