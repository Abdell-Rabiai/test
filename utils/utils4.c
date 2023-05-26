#include "../include/minishell.h"


void builtin_execution(t_list *shell, t_info *info, int flag)
{
	t_cmd *commands;

	commands = shell->data;

	if (flag == 1)
	{
		if (commands->fd_in != -1)
		{
			dup2(commands->fd_in, 0);
			close(commands->fd_in);
		}
		else
		{
			printf("minishell: %s: No such file or directory\n", commands->file_name);
			exit(EXIT_FAILURE);
		}
		if (commands->fd_out != 1)
		{
			dup2(commands->fd_out, 1);
			close(commands->fd_out);
		}
	}
	if (!commands || !commands->cmds[0])
		return ;
	if (!ft_strcmp(commands->main_cmd, "echo"))
		my_echo(commands);
	else if (!ft_strcmp(commands->main_cmd, "cd"))
		my_cd(commands, info);
	else if (!ft_strcmp(commands->main_cmd, "pwd"))
		my_pwd();
	else if ((!ft_strcmp(commands->main_cmd, "export") 
		&& !commands->cmds[1]) || (commands->cmds[1]
		&& commands->cmds[1][0] == '\0' && !commands->cmds[2]))
			print_list_export(info);
	else if (info->head_en && !ft_strcmp(commands->main_cmd, "env") 
		&& !(commands->cmds[1]))
		print_list_env(info);
	else if (!ft_strcmp(commands->main_cmd, "export") 
		&& commands->cmds[1])
	{
		if (info->head_en && check_export(commands->cmds) == 0)
			return ;
		if (info->head_en && commands->cmds)
		{
			add_export(&info->head_ex, commands->cmds);
			add_env(&info->head_en, commands->cmds);
		}
	}
	else if (!ft_strcmp(commands->main_cmd, "exit"))
		my_exit();
	else if (info->head_en && info->head_ex 
		&& !ft_strcmp(commands->main_cmd, "unset"))
		my_unset(commands, info);
}
void	choose_command(t_list *shell, t_info *info)
{
	info->in = dup(STDIN_FILENO);
    info->out = dup(STDOUT_FILENO);
	t_cmd *commands;

	commands = shell->data;
	if (((t_cmd*)(shell->next)) == NULL)
		execute_commande(commands, info, shell);
	else if (commands->main_cmd && ((t_cmd*)(shell->next)) != NULL)
		execute_commands_with_pipe(shell, info);
	else
		printf("minishell: %s: command not found\n", commands->cmds[0]);
	dup2(info->in, STDIN_FILENO);
	dup2(info->out, STDOUT_FILENO);
	close(info->in);
	close(info->out);
}

int	count_words_me(char *str, char c)
{
	int	count;
	int	find;

	count = 0;
	find = 0;
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str != c && find == 0)
		{
			find = 1;
			count++;
		}
		else if (*str == c)
			find = 0;
		str++;
	}
	return (count + 1);
}