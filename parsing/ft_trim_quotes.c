/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:30:35 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/07 19:46:55 by aben-nei         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"

void	ft_trim_quotes(t_list **args)
{
	t_list	*current;
	char	*string;
	char	*tmp;
	int		i;
	int		j;

	current = *args;
	while (current)
	{
		i = 0;
		j = 0;
		string = ((t_token *)(current->data))->value;
		tmp = malloc(ft_strlen(string) + 1);
		while (string[i])
		{
			if (string[i] == '\'')
			{
				i++;
				while (string[i] != '\'')
					tmp[j++] = string[i++];
				break ;
			}
			else if (string[i] == '\"')
			{
				i++;
				while (string[i] != '\"')
					tmp[j++] = string[i++];
					break;
			}
			else
				tmp[j++] = string[i];
			i++;
		}
		tmp[j] = '\0';
		free(((t_token *)(current->data))->value);
		((t_token *)(current->data))->value = tmp;
		current = current->next;
	}
}
