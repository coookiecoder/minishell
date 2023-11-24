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

typedef struct s_shell {
	char	**env;
	char	*prompt;
}	t_shell;

typedef struct s_command {
	char		bin[PATH_MAX];
	int			argc;
	char		**argv;
}	t_command;

// builtin/cd.c

int		cd(int argc, char **argv, t_shell *shell);

// builtin/pwd.c

int		pwd(char **envp);

// core/environment.c

int		load_env(t_shell *sh, const char **envp);
void	set_env(t_shell *sh, const char *name, const char *value);
void	unset_env(t_shell *sh, const char *name);
char	*get_env(t_shell *sh, const char *name);
void	unload_env(t_shell *sh);

// core/format_command.c

void	format_command(char *buffer, t_command *command);

// core/make_command.c

int		make_command(t_command command, t_shell *shell);

// utlis/strncmp.c

int		ft_strncmp(const char *s1, const char *s2, int len);

// utlis/strlen.c

int		ft_strlen(const char *str);

// utlis/strdup.c

char	*ft_strdup(const char *s);

#endif
