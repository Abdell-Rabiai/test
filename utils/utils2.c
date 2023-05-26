/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:46:09 by ahaloui           #+#    #+#             */
/*   Updated: 2023/05/26 22:17:58 by arabiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char  **join_path_command(char *command, t_export **head_ex)
{
    char *path;
    char **split_paths;
    int i;
    
    path = get_value(head_ex, "PATH");
    if (!path)
        return (NULL);
    split_paths = ft_split(path, ':');
    i = 0;
    while (split_paths[i])
    {
        split_paths[i] = ft_strjoin(split_paths[i], "/");
        split_paths[i] = ft_strjoin(split_paths[i], command);
        i++;
    }
    return (split_paths);
}

int is_builin(t_cmd *commands)
{
    if (ft_strcmp(commands->main_cmd, "echo") == 0)
        return (1);
    else if (ft_strcmp(commands->main_cmd, "cd") == 0)
        return (1);
    else if (ft_strcmp(commands->main_cmd, "pwd") == 0)
        return (1);
    else if (ft_strcmp(commands->main_cmd, "export") == 0)
        return (1);
    else if (ft_strcmp(commands->main_cmd, "unset") == 0)
        return (1);
    else if (ft_strcmp(commands->main_cmd, "env") == 0)
        return (1);
    else if (ft_strcmp(commands->main_cmd, "exit") == 0)
        return (1);
    return (0);
}

char  *check_if_command_found(char *command, t_export **head_ex)
{
    char **split_paths;
    int i;
    
    split_paths = join_path_command(command, head_ex);
    if (!split_paths)
        return (NULL);
    i = 0;
    while (split_paths[i])
    {
        if (access(split_paths[i], F_OK | X_OK) == 0)
            return (split_paths[i]);
        i++;
    }
    return (NULL);
}

int check_if_command_exit(t_cmd *commands, t_info *info)
{
    if (check_if_command_found(commands->main_cmd, &info->head_ex))
        return (1);
    return (0);
}
void execute_commande(t_cmd *commands, t_info *info, t_list *shell)
{
    if (is_builin(commands) == 1)
        builtin_execution(shell, info, 1);
    else if (check_if_command_found(commands->main_cmd, &info->head_ex))
    {
        pid_t pid;
        
        pid = fork();
        if (pid == -1) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) 
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
            if (execve(check_if_command_found(commands->main_cmd, &info->head_ex), commands->cmds, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
             wait(NULL);
        }
    }
    // close(commands->fd_in);
    // close(commands->fd_out);
}

// function to handle the ctrl + c
