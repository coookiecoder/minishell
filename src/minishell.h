/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   NOOT NOOT MOTHER FUCKER                      :#:  :#:         :#:  :#:   */
/*                                                :#:  :#::#     #::#:  :#:   */
/*   By: an asshole who like to break thing       :#:  :#::#: # :#::#:  :#:   */
/*                                                :##::##: :#:#:#: :##::##:   */
/*   Created: the-day-it-was created by UwU        :####:  :##:##:  :####:    */
/*   Updated: the-day-it-was updated by UwU                                   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

# define SHELL_PROMPT "UwU-Shell $> "
# define SHELL_PROMPT_N 13

# define ERR_UNKNOWN_CMD "bash: command not found\n"
# define ERR_UNKNOWN_CMD_N 24

# define ERR_PIPES_FILE "bash: No such file or directory\n"
# define ERR_PIPES_FILE_N 32

# define WARN_PIPES_TEMP "bash: warning: here-document delimited by EOF\n"
# define WARN_PIPES_TEMP_N 46

# define ERR_PIPES_FAIL "bash: failure to open new FDs\n"
# define ERR_PIPES_FAIL_N 30

# define ERR_PARSE_MEMORY "bash: memory allocation failed\n"
# define ERR_PARSE_MEMORY_N 31

# define ERR_PARSE_SYNTAX "bash: syntax error\n"
# define ERR_PARSE_SYNTAX_N 19

enum e_sighandle {
	NORMAL = 0,
	EXECUTION,
	EDITMODE,
	EXIT
};

enum e_quotetype {
	NO_QUOTE = 0,
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"'
};

enum e_target {
	NEITHER = 0,
	LEFT,
	RIGHT,
	BOTH
};

// Used for handling SIGNALs while running execve and forks tasks
extern enum e_sighandle	g_sig;

typedef struct s_shell {
	int		last_code;
	char	**env;
}	t_shell;

typedef struct s_command {
	char		*raw;
	char		bin[PATH_MAX];
	int			argc;
	char		**argv;
	int			fd_in;
	int			fd_out;
}	t_command;

typedef struct s_execute {
	size_t		total;
	t_command	**cmds;
	int			fds_odd[2];
	int			fds_even[2];
}	t_exec;

// builtin/cd.c

int		cd(int argc, char **argv, t_shell *shell);

// builtin/pwd.c

int		pwd(void);

// builtin/echo.c

int		echo(int argc, char **argv);

// builtin/error.c

int		convert_code(char *code);

// builtin/env.c

int		env(t_shell *shell);

// builtin/export.c

int		ft_export(t_shell *sh, t_command command);

// builtin/unset.c

int		keep_env(char *env, t_command cmd);

// core/environment.c

int		load_env(t_shell *sh, const char **envp);
int		set_env(t_shell *sh, char *raw);
int		unset_env(t_shell *sh, t_command command);
char	*get_env(t_shell *sh, const char *name);
void	unload_env(t_shell *sh);

// core/format_command.c

void	format_command(char *buffer, t_command *command);

// core/make_command.c

int		make_command(
			t_command command, t_shell *shell, t_exec *exe, size_t pos);

// core/cleanup.c

void	ft_free(char *buffer, t_shell *shell, t_command *command);
int		ft_exit(char *buffer, t_shell *shell, t_command *command);
void	ft_freecmd(t_command *cmd);
void	ft_freeexec(t_exec *exe);

// core/raw_parsing.c

void	init_command(t_command *command);
int		raw_parse(t_shell *sh, char *raw);
void	assign_quote_value(enum e_quotetype *v, char c);
char	*expension(t_shell *sh, char *raw);

// core/piping.c

void	new_pipe(size_t pos, t_exec *exec);
void	duplicate_input(size_t pos, t_exec *exe);
void	duplicate_output(size_t pos, t_exec *exe);
void	close_fd(size_t pos, t_exec *exe);

// core/signal.c

void	signal_handler(int sig);
void	signal_breakout(int sig);

// core/redirects.c

char	*redirection_handler(char *raw, t_command *cmd);

// utlis/strncmp.c

int		ft_strncmp(const char *s1, const char *s2, int len);

// utlis/strlen.c

int		ft_strlen(const char *str);
int		ft_strclen(const char *str, const char stop);

// utlis/strdup.c

char	*ft_strndup(const char *s, size_t n);
char	*ft_strdup(const char *s);

// utlis/atolli.c

int		atolli(char *number);
char	*ft_itoa(int n);

// utils/strjoin.c

char	*ft_strjoin(char *string_a, char *string_b, int mode, size_t n);

// utlis/is_space.c

int		ft_is_space(char c);
int		is_empty(const char *buffer);

// === NORME ABUSE BE LIKE === //
typedef struct s__exp {
	enum e_quotetype	quote;
	char				*tmp;
	int					x;
	int					y;
}	t__exp;

#endif
