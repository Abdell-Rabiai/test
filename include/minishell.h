/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:32:14 by aben-nei          #+#    #+#             */
/*   Updated: 2023/05/26 22:03:30 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include   <signal.h>


enum e_type
{
	FLAG,
	WORD,
	DQUATES,
	SQUATES,
	PIPE,
	RED_OUT,
	RED_INP,
	RED_APP,
	W_SPACE,
	HEREDOC,
	EOFILE,
	RED_APP_FILE,
	RED_FILE,
	FILE_INP,
	VAR,
};

#define READ_END 0
#define WRITE_END 1


typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

// typedef struct s_heredocs
// {
// 	char			*limiter;
// 	char 			*filename;
// }					t_heredocs;


typedef struct s_token
{
	int			key;
	char		*value;
	int			flag_quote;
}					t_token;

typedef struct s_cmd
{
	char		**cmds; // {ls} {-la} {NULL}
	int			fd_in;//0
	int			fd_out; //3
	char 		*main_cmd; //ls
	char		*file_name;
}					t_cmd;


typedef struct s_init
{
	int		ac;
	char	**av;
	char	**environ;
}	t_init;

typedef struct s_env
{
	char	*env_var;
	char	*env_value;
	struct s_env *next;
}				t_env;

typedef struct s_export
{
	char 	*export_var;
	char 	*export_value;
	struct s_export *next;
}				t_export;

typedef struct s_info 
{
	t_env	*head_en;
	t_export *head_ex;
	int		in;
	int		out;
}			t_info;

// file my_echo.c
int			my_echo(t_cmd *cmd);
int			check_option(char *cmd);
char		*get_last_split(t_cmd *cmd);

// file my_pwd.c
int my_pwd();

int is_builin(t_cmd *commands);
void builtin_execution(t_list *shell, t_info *info, int flag);
// file my_cd.c
char		*get_path_home(t_export **head_ex);
char		*get_old_path(t_export **head_ex);
char 		*get_path(t_export **head_ex);
void		set_value(t_export **head_ex, char *export_var, char *new_value);
void		init_pwd(t_export **head_ex);
int			get_pos(char *str, char c);
int 		my_cd(t_cmd *commands, t_info *info);

// file my_export.c
t_export	*ft_lst_new_export(char *export_var, char *export_value);
void		ft_lst_add_back_export(t_export **head_ex, t_export *new);
char		*get_export_variable(char *variable);
char 		*get_export_value(char *value);
void		add_export_element(char *export_var, char *export_value, t_export **head_ex);
void 		print_list_export(t_info *info);
void		sort_export_list(t_export **head_ex);
int			check_is_empty_string(char *str);
int			check_if_export_var_exist(t_export *head_ex, char *export_var);
void		remove_export_element(t_export **head_ex, char *export_var);
void 		fill_export_list(char **environ, t_export **head_ex);

// file my_env.c
t_env		*ft_lst_new_env(char *env_var, char *env_value);
void		ft_lst_add_back_env(t_env **head_en, t_env *new);
char		*get_env_variable(char *variable);
char 		*get_env_value(char *value);
void		add_env_element(char *env_var, char *env_value, t_env **head_en);
void 		print_list_env(t_info *info);
int			check_is_empty_string_env(char *str);
int			check_if_env_var_exist(t_env *head_en, char *env_var);
void		remove_env_element(t_env **head_en, char *env_var);
void		fill_env_list(char **environ, t_env **head_env);

// file my_unset.c
void 		my_unset(t_cmd *commands, t_info *info);

// file my_exit.c
int			my_exit();

// file utils1.c
void		cast_variables(int ac, char **av, char **environ);
int			ft_strcmp(char *s1, char *s2);
int			is_directory(char* command);
char		*get_value(t_export **head_ex, char *var);

// file utils2.c
char		**join_path_command(char *command, t_export **head_ex);
char		*check_if_command_found(char *command, t_export **head_ex);
int 		check_if_command_exit(t_cmd *commands, t_info *info);
void 		execute_commande(t_cmd *commands, t_info *info, t_list *shell);


// file utils3.c
void 		execute_commands_with_pipe(t_list *cmd, t_info *info);

// file help_export.c
int			check_export(char **split);
void    	concatenation_export(t_export **head_ex,char *export_variable, char *new_value);
void		add_export(t_export **head_ex, char **split);
int			check_if_valid_args(char *split);

// file help_env.c
void		add_env(t_env **head,  char **split);
void 		concatenation_env(t_env **head_en, char *env_var, char *new_value);
//





/*--------------- list ------------------------*/
t_list	*ft_lstnew(void	*content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
/*-----------------------------------------------*/
void	ft_heredoc(t_list *args, t_list **cmd);
void	get_token(char *input, t_list **token);
int		syntex_error(t_list *list);
int		check_quotes(char *input);
void 	fill_env_list(char **environ, t_env **head_env);
int 	ft_strcmp(char *s1, char *s2);
void	ft_trim_quotes(t_list **args);
void	ft_join_args(t_list **args);
void	ft_expand(t_list **list, t_env *env);
void	ft_remove_node(t_list **head, t_list *node);
char	*skip_whitespace(char *input);
int		ft_whitespace(char c);
int		get_number_of_commands(t_list *args);
int		get_number_of_commands(t_list *args);
void	rederection_out(t_list *args, int *fd_out);
void	rederection_in(t_list *args, int *fd_in, char **file_name);
void	rederection_app(t_list *args, int *fd_out);
void	fill_cmd(t_list **cmd, int fd_in, int fd_out, char *file_name, char **args);
void	command_table(t_list *args, t_list **cmd);
int		allocate_commande(t_list *args);
char	**get_command1(t_list *args);


// utils
int		count_words_me(char *str, char c);
void	choose_command(t_list *shell, t_info *info);



#endif
