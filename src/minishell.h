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

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/wait.h>

enum e_quotetype {
	NO_QUOTE = 0,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
};

enum e_target {
	NEITHER = 0,
	LEFT,
	RIGHT,
	BOTH
};

typedef struct s_shell {
	char	**env;
}	t_shell;

typedef struct s_command {
	char		bin[PATH_MAX];
	int			argc;
	char		**argv;
}	t_command;

typedef struct s_execute {
	size_t		total;
	t_command	**cmds;
	int			in_fd;
	int			in_at;
	int			out_fd;
	int			out_at;
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

int		make_command(t_command command, t_shell *shell);

// core/cleanup.c

void	ft_free(char *buffer, t_shell *shell, t_command *command);
int		ft_exit(char *buffer, t_shell *shell, t_command *command);
void	ft_freecmd(t_command *cmd);

// core/raw_parsing.c

int		raw_parse(t_shell *sh, char *raw);

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

// utils/strjoin.c

char	*ft_strjoin(char *string_a, char *string_b, int mode, size_t n);

// === NORME ABUSE BE LIKE === //
typedef struct s__exp {
	enum e_quotetype	quote;
	char				*tmp;
	int					x;
}	t__exp;

#endif
