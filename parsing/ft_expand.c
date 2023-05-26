/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:25:33 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/17 01:13:51 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_variable_name(char *name)
{
	int		i;
	int		end;
	int		j;
	int		flag;
	char	*str;

	i = 0;
	j = 0;
	flag = 0;
	end = ft_strlen(name) - 1;
	str = (char *)malloc(ft_strlen(name) + 1);
	while (name[i])
	{
		while (name[i] && (name[i] == '\'' || name[i] == '\"' || name[i] == '|'))
			i++;
		while (name[end] && (name[end] == '\'' || name[end] == '\"' || name[end] == '|'))
			end--;
		if (name[i] == '$')
			i++;
		while (name[i] && name[i] != '$' && name[i] != ' '&& i <= end) //"'$USER'"
		{
			str[j++] = name[i];
			i++;
			flag = 1;
		}
		if (flag)
			str[j] = '\0';
		break ;
	}
	return (str);//free(name);
}

void	ft_expand(t_list **list, t_env *env)
{
	t_list		*tmp;
	t_env		*tmp_env;
	int			i;
	int			len;
	char        *str;
	char        *string;

    tmp = *list;
	tmp_env = env;
	while (tmp)
	{
		// printf("[%s]\n", ((t_token *)(tmp->data))->value);
		if (tmp && ((t_token *)(tmp->data))->key == VAR)
		{
			while (env)
			{
				if (tmp && !ft_strcmp(env->env_var, get_variable_name(((t_token *)(tmp->data))->value)))
				{
					((t_token *)(tmp->data))->value = ft_strdup(env->env_value); // allocate
					break ;
				}
				env = env->next;
			}
			if (ft_strlen(((t_token *)(tmp->data))->value) == 1)
			{
				((t_token *)(tmp->data))->value = ft_strdup("$"); //malloc
				// free (tmp->data);
				// (tmp->data) = NULL;
			}
			else if (!env)
			{
				((t_token *)(tmp->data))->value = ft_strdup(""); //malloc
				// free (tmp->data);
				// (tmp->data) = NULL;
			}
			env = tmp_env;
		}
		else if (tmp && ((t_token *)(tmp->data))->key == DQUATES)
		{
			i = 0;
			// j = 0;
			string = NULL;
			while (((t_token *)(tmp->data))->value[i])
			{
				// string = NULL;
				// printf("s = [%s] | i = %d\n", &((t_token *)(tmp->data))->value[i], i);
				len = 0;
				while (((t_token *)(tmp->data))->value[i + len]
					&& ((t_token *)(tmp->data))->value[i + len] != '$')
					len++;
				if (len > 0)
					string = ft_strjoin(string, ft_substr(((t_token *)(tmp->data))->value, i, len));
					// printf("len = %d | i = %d | string(0) = [%s]\n", len, i,  string);
				i +=len;
				if (((t_token *)(tmp->data))->value[i] == '$')
				{
					if (((t_token *)(tmp->data))->value[i + 1] == '\0' || !ft_isalnum(((t_token *)(tmp->data))->value[i + 1]))
					{
						len = 1;
						while (((t_token *)(tmp->data))->value[i + len] && !ft_isalnum(((t_token *)(tmp->data))->value[i + len]))
							len++;
						if (len >0)
							string = ft_strjoin(string, ft_substr(((t_token *)(tmp->data))->value, i, len));
						i += len;
					}
					else if (((t_token *)(tmp->data))->value[i] == '$')
					{
						i++;
						if (ft_isdigit(((t_token *)(tmp->data))->value[i]))
						{
							i++;
							continue ;
						}
					}
					else if (((t_token *)(tmp->data))->value[i + 1] && !ft_isalpha(((t_token *)(tmp->data))->value[i + 1])
						&& ((t_token *)(tmp->data))->value[i + 1] != '_')
						{
							len = 0;
							while (((t_token *)(tmp->data))->value[i + len] && !ft_isalpha(((t_token *)(tmp->data))->value[i + len])
									&& ((t_token *)(tmp->data))->value[i + len] != '_')
									len++;
							if (len > 0)
								string = ft_strjoin(string, ft_substr(((t_token *)(tmp->data))->value, i, len));
							i += len;
						}
					len = 0;
					while (((t_token *)(tmp->data))->value[i + len]
						&& ((t_token *)(tmp->data))->value[i + len] != '$'
						&& ((t_token *)(tmp->data))->value[i + len] != ' ' && (ft_isalpha(((t_token *)(tmp->data))->value[i + len])
									|| ((t_token *)(tmp->data))->value[i + len] == '_'))
							len++;
					str = ft_substr(((t_token *)(tmp->data))->value, i, len);
					i += len;
				while (env)
				{
					if (tmp && !ft_strcmp(env->env_var, str))
					{
						if (len > 0)
							string = ft_strjoin(string, env->env_value); // allocate
						break ;
					}
					env = env->next;
				}
				// if (!env)
				// 	string = ft_strjoin(string, str); // allocate
					env = tmp_env;
				}
			}
			// printf("string = [%s]\n", string);
			if (string)
				((t_token *)tmp->data)->value = string;
		// free(string);
		}
		// printf("string = [%s]\n", string);
		tmp = tmp->next;
	}
}

// --laaasaaaaaaaaaaa
// --laaasaaaaaaaaaaaa
// --laaasaaaaaaaaaaaa