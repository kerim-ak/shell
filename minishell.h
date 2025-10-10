#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

extern volatile sig_atomic_t	g_signal;

typedef enum e_quote_state
{
	Q_DEFAULT,
	Q_IN_SINGLE,
	Q_IN_DOUBLE
}	t_quote_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_redir
{
	char			*filename;
	t_token_type	type;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}	t_env;

typedef struct s_minishell
{
	t_cmd	*commands;
	t_env	*env_list;
	int		last_exit_code;
	int		should_exit;
}	t_minishell;

//-----------------BUILTINS------------------//
		//cd.c
int		ft_cd(char **argv, t_minishell *shell);

		//echo.c
int		ft_echo(char **argv);

		//export_utils.c
int		is_valid_identifier(const char *str);
int		extract_key_value(const char *arg, char **key, char **value);
void	update_or_add_env(t_minishell *shell, char *key, char *value);
int		env_has_key(t_env *env, const char *key);

		//export.c
int		ft_export(t_minishell *shell, char **argv);

		//others.c
int		ft_pwd(void);
int		ft_cd(char **argv, t_minishell *shell);
int		ft_exit(char **argv, t_minishell *shell);
int		ft_env(char **argv, t_minishell *shell);

		//unset.c
int		ft_unset(t_minishell *shell, char **argv);

//-------------------EXE-------------------//
		//builtin.c
int		builtin_check(char **argv);
int		exec_builtin(char **argv, t_minishell *shell);
void	exec_builtin_or_continue(t_minishell *shell, t_cmd *cmd, pid_t *pids);

		//exec_child.c
void	execute_child(t_minishell *shell, t_cmd *cmd, pid_t *pids);

		//executor_helpers.c
int		executor_builtin(t_cmd *cmd, t_minishell *shell);
int		is_single_builtin(t_cmd *cmd);
pid_t	*init_child_pid_array(int cmd_count);
void	if_exec(int pid, t_minishell *shell, t_cmd *cmd, pid_t *pids);

		//executor.c
void	executor(t_minishell *shell, int i);

		//find_command_path.c
char	*find_command_path(char *cmd, t_env *env_list);

		//heredoc_helpers.c
char	*expand_heredoc_line(char *line, t_minishell *shell);
void	cleanup_heredoc_fds(t_cmd *cmd);

		//heredoc_helpers2.c
int		heredoc_fork_child(int write_fd, char *delim, t_minishell *shell);

		//heredoc_helpers3.c
int		process_single_heredoc(t_redir *redir, t_minishell *shell);

		//heredoc.c
int		process_all_heredocs(t_minishell *shell);

		//path_exec.c
char	*resolve_command_path(t_minishell *shell, t_cmd *cmd, pid_t *pids);
void	handle_execve_error(char *cmdp, char *cmd, t_minishell *sh, pid_t *ps);

		//pipe_helpers.c
int		count_commands(t_cmd *cmd);
int		**create_pipes(int cmd_count);
void	free_pipes(int **pipes, int cmd_count);
void	setup_child_pipes(int i, int cmd_count, int **pipes);
void	close_all_pipes(int **pipes, int cmd_count);

		//redir.c
int		apply_redirections(t_cmd *cmd, t_minishell *shell);

		//wait_utils.c
void	wait_all_children(pid_t *pids, int cmd_count, t_minishell *shell);
//----------------UTILS--------------------//
		//command_utils.c
t_cmd	*build_commands(t_token *tokens);
void	free_commands(t_cmd **cmds);

		//env_utils.c
size_t	env_len(t_env *env);
t_env	*initialize_env(char **envp);
void	free_env_list(t_env **env_list);
char	*get_env_value(char *key, t_env *env_list);

		//redir_utils.c
t_redir	*new_redir_node(t_token_type type, char *filename);
void	add_redir_to_back(t_redir **list, t_redir *new_node);
void	free_redirs(t_redir **list);

		//string_utils_more.c
char	*str_append(char *base, char *to_append);
char	*char_append(char *base, char c);
void	free_str_array(char **arr);
char	*ft_strjoin_char(char *s1, char c);

		//string_utils.c
int		ft_strcmp(const char *s1, const char *s2);
char	**env_list_to_array(t_env *env);

		//token_utils.c
t_token	*tok_new(char *text, t_token_type type);
void	tok_add_back(t_token **lst, t_token *new_token);
void	tok_clear(t_token **lst);

//------------------PARSER------------------//
		//dollar_expansion.c
char	*handle_dollar_expansion(int *i, char *raw, t_minishell *shell,
			t_quote_state q_state);

		//expand.c
char	*expand(char *raw, t_minishell *shell, t_quote_state q_state, int i);
		//expander.c
t_token	*expander(t_token *tokens, t_minishell *shell);

		//parser.c
int		parser(t_minishell *shell_data, char *line);

		//tokenizer.c
t_token	*tokenizer(const char *line);

//-----------------------------------------------//
int		main_loop(t_minishell *shell);

#endif
