/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:29:42 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/12 23:08:20 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
        return (1);
    return (0);
}

void	fill_token(t_list **args, int token, char *word)
{
	t_token	*tokens;

	if (word)
	{
		tokens = (t_token *)malloc(sizeof(t_token));
		tokens->value = word;
		if (token == DQUATES)
		{
			tokens->key = token;
			tokens->flag_quote = 1;
		}
		else
			tokens->key = token;
		ft_lstadd_back(args, ft_lstnew(tokens));
	}
	
}

char	*skip_whitespace(char *input)
{
	int		i;
	int		start;
	int		end;
	int		len;
	char	*string ;
	
	i = 0;
	start = 0;
	end = 0;
	len = ft_strlen(input) - 1;
	string = NULL;
	while (input[i] && ft_whitespace(input[i]))
		i++;
	start = i;
	while (input[len] && ft_whitespace(input[len]) )
		len--;
	if (len >= 0)
		end = len;
	if (start < end)
		string = malloc((end - start) + 2); // allocate memory for the string
	else
		string = malloc((start - end) + 2);
	i = 0;
	while (input[start] && start <= end)
		string[i++] = input[start++];
	string[i] = '\0';
	return (string);
}

void	get_token(char *input, t_list **token)
{
	int	i;
	int	len;
	int	flag;
	t_token	*word;

	i = 0;
	flag = 1;
	word = (t_token *)malloc(sizeof(t_token));
	if (!word)
		return ;
	input = skip_whitespace(input);
	while (input && input[i])
	{
		if (input[i] && !ft_whitespace(input[i]) && input[i] != '\"' && input[i] != '\'' && input[i] != '<'
			&& input[i] != '>' && input[i] != '|' && input[i] != '$' && flag && input[i] != '-')
		{
			len = 0;
			while (input[i + len] && input[i + len] != '-' && !ft_whitespace(input[i + len]) && input[i + len] != '\"'
				&& input[i + len] != '\'' && input[i + len] != '<' && input[i + len] != '>' && input[i + len] != '$' && input[i + len] != '|')
					len++;
			if (len > 0 && flag)
			{
				fill_token(token, WORD, ft_substr(input, i, len));
				flag = 0;
			}
			i += len;
			len = 0;
			while (input[i + len] && ft_whitespace(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, W_SPACE, ft_substr(input, i, len));
			i += len;
		}
		else if ((input[i] && input[i] != '\'' && !ft_whitespace(input[i]) && input[i] != '|' && input[i] != '\"'
			&& input[i] != '<' && input[i] != '>' && input[i] != '$' && !flag) || input[i] == '-')
		{
			len = 0;
			while (input[i + len] && input[i + len] != ' '&& input[i + len] != '\'' && input[i + len] != '\"'
			 	&& input[i + len] != '<' && input[i + len] != '>' && input[i + len] != '$' && input[i + len] != '|')
				len++;
			if (len > 0)
				fill_token(token, FLAG, ft_substr(input, i, len));
			i += len;
		}
		else if (input[i] && input[i] == '|')
		{
			len = 0;
			while (input[i + len] && ft_whitespace(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, W_SPACE, ft_substr(input, i, len));
			i += len;
			len = 0;
			while (input[i + len] && input[i + len] == '|' && !ft_whitespace(input[i + len]))
				len++;
				fill_token(token, PIPE, ft_substr(input, i, len));
            i += len;
			flag = 1;
		}
		else if (input[i] && ft_whitespace(input[i]))
		{
			len = 0;
			while (input[i + len] && ft_whitespace(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, W_SPACE, ft_substr(input, i, len));
			i += len;
		}
		else if (input[i] && input[i] == '\"')
		{
			len = 1;
			while (input[i + len] && input[i + len] != '\"')
				len++;
			if (len > 0)
				fill_token(token, DQUATES, ft_substr(input, i, len + 1));
			i += len + 1;
		}
		else if (input[i] && input[i] == '\'')
		{
			len = 1;
			while (input[i + len] && input[i + len] != '\'')
				len++;
			if (len > 0)
				fill_token(token, SQUATES, ft_substr(input, i, len + 1));
			i += len + 1;
		}
		else if (input[i] && input[i] == '>' && input[i + 1] != '>') // >
		{
			fill_token(token, RED_OUT, ft_substr(input, i, 1));
			len = 0;
			i += 1;
			while (input[i + len] && ft_whitespace(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, W_SPACE, ft_substr(input, i, len));
			i += len;
			len = 0;
			while (input[i + len] && !ft_whitespace(input[i + len]) && input[i + len] != '\"' && input[i + len] != '\''
				&& input[i + len] != '<' && input[i + len] != '>' && input[i + len] != '|' && input[i + len] != '$')
					len++;
				if (len > 0)
					fill_token(token, RED_FILE, ft_substr(input, i, len));
			i += len;
		}
		else if (input[i] && input[i] == '<' && input[i + 1] != '<') // <
		{
			fill_token(token, RED_INP, ft_substr(input, i, 1));
			len = 0;
			i += 1;
			while (input[i + len] && ft_whitespace(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, W_SPACE, ft_substr(input, i, len));
			i += len;
			len = 0;
			while (input[i + len] && !ft_whitespace(input[i + len]) && input[i + len] != '\"' && input[i + len] != '\''
			&& input[i + len] != '<' && input[i + len] != '>' && input[i + len] != '|' && input[i + len] != '$' && ft_isalnum(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, FILE_INP, ft_substr(input, i, len));
			i += len;
			
		}
		else if (input[i] && input[i] == '>' && input[i + 1] == '>') // >>
		{
			fill_token(token, RED_APP, ft_substr(input, i, 2));
			len = 0;
			i += 2;
			while (input[i + len] && ft_whitespace(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, W_SPACE, ft_substr(input, i, len));
			i += len;
			len = 0;
			while (input[i + len] && !ft_whitespace(input[i + len]) && input[i + len] != '\"' && input[i + len] != '\''
			&& input[i + len] != '<' && input[i + len] != '>' && input[i + len] != '|' && input[i + len] != '$' && ft_isalnum(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, RED_APP_FILE, ft_substr(input ,i, len));
			i += len;
		}
		else if (input[i] && input[i] == '<' && input[i + 1] == '<') // <<
		{
			fill_token(token, HEREDOC, ft_substr(input, i, 2));
			len = 0;
			i += 2;
			while (input[i + len] && ft_whitespace(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, W_SPACE, ft_substr(input, i, len));
			i += len;
			len = 0;
			while (input[i + len] && !ft_whitespace(input[i + len]) && input[i + len] != '<'
				&& input[i + len] != '>' && input[i + len] != '|' && input[i + len] != '$' && ft_isalnum(input[i + len]))
				len++;
			if (len > 0)
				fill_token(token, EOFILE, ft_substr(input ,i, len));
			i += len;
		}
		else if (input[i] && input[i] == '$') // $
		{
			len = 1;
			while (input[i + len] && !ft_whitespace(input[i + len]) && input[i + len] != '$' && !ft_strchr("$\"'+-./:;<=>?@[\\]^_`{|}~%#&()*,;=[]", input[i + len])
				&& input[i + len] != '\'' && input[i + len] != '\"' && input[i + len] != '|' && input[i + len] != '<' && input[i + len] != '>')
				len++;
			if (len > 0)
				fill_token(token, VAR, ft_substr(input, i, len));
			i += len;
		}
	}
	free(input);
}
