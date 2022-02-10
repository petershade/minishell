//
// Created by  Akulova Ekaterina on 05.02.2022.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# define BUFFER 1024

char buff[BUFFER];

int is_znak(char c);
int is_pipe(char *str);
int what_quotes(char *str);
int get_cmd(void);
char **do_parse(char *buff);
void do_redirect(char *buff);
int do_exec(char *buff);

#endif //MINISHELL_MINISHELL_H
