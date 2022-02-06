//
// Created by  Akulova Ekaterina on 05.02.2022.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# define BUFFER 1024

char buffer[BUFFER];

#endif //MINISHELL_MINISHELL_H
