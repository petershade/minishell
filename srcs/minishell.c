//
// Created by  Akulova Ekaterina on 05.02.2022.
//
#include "../minishell.h"
#include <string.h>

int is_znak(char c)
{
    if (c == '<' || c == '>')
        return (1);
    return (0);
}

int	is_separator(char c)
{
    if (c == ' ' || c == '<' || c == '>')
        return (1);
    return (0);
}


int is_pipe(char *str)
{
    int i;
    int pipe;

    pipe = 0;
    while (str[i])
    {
        if (str[i] == '|')
            pipe++;
        i++;
    }
    return (pipe);
}

int what_quotes(char *str)
{
    int i;
    int quote;

    i = 0;
    quote = 0;
    while (str[i])
    {
        if (str[i] == '"')
        {
            if (quote == 0)
                quote = 2;
            else if (quote == 2)
                quote = 0;
        }
        if (str[i] == '\'')
        {
            if (quote == 0)
                quote = 1;
            else if (quote == 1)
                quote = 0;
        }
        i++;
    }
    return (quote);
}

int get_cmd(void)
{
    memset(buff, 0x00, BUFFER);
    //printf("minishell$ ");
    fflush(stdout);
    // Отображение аналогового терминала

    fgets(buff, BUFFER - 1, stdin);
    buff[strlen(buff) - 1] = '\0';
    return 0;

}

// 2. Разбираем команду
char **do_parse(char *buff)
{
    char *ptr = buff;
    int argc = 0;
    static char *argv[32];

    while('\0' != *ptr)
    {
        if(' ' != *ptr)
        {
            argv[argc++] = ptr;
            while('\0' != *ptr && ' ' != *ptr)
                ptr++;
            *ptr = '\0';
        }
        ptr++;
    }
    // Удаляем пробелы и извлекаем команды

    argv[argc] = NULL;
    return argv;
}

void do_redirect(char *buff)
{
    int redirect_flag = 0;
    char *redirect_file = NULL;
    char *ptr = buff;

    while(*ptr != '\0')
    {
        if(*ptr == '>')
        {
            *ptr++ = '\0';
            ++redirect_flag;

            if(*ptr == '>')
            {
                ++redirect_flag;
                ptr++;
            }

            while(*ptr == ' ' && *ptr != '\0')
                ptr++;

            redirect_file = ptr;

            while(*ptr != ' ' && *ptr != '\0')
                ptr++;

            *ptr = '\0';
        }
        ptr++;
    }

    if (redirect_flag == 1)
    {
        int fd = open(redirect_file, O_WRONLY|O_CREAT|O_TRUNC, 0664);
        if (fd < 0)
        {
            perror("Open error");
            exit(-1);
        }
        dup2(fd, 1);
    }
    else if(redirect_flag == 2)
    {
        int fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
        if (fd < 0)
        {
            perror("Open error");
            exit(-1);
        }
        dup2(fd, 1);
    }
}

// 4. Замена программы
int do_exec(char *buff)
{
    char **argv = { NULL };

    int pid = fork();
    // Создаем дочерний процесс, заменяем программу в дочернем процессе
    if (0 == pid)
    {
        do_redirect(buff);
        argv = do_parse(buff);

        if(NULL != argv[0])
        {
            execvp(argv[0], argv);
            // Процесс замены
        }
        else
        {
            exit(-1);
            // Если вы ввели ошибку в команде, выходим из процесса
        }

    }
    else
    {
        waitpid(pid, NULL, 0);
        // Ждем завершения дочернего процесса
    }

    return 0;
}

int main(int argc, char **argv, char **envp)
{
    char *str;

    while(1)
    {
        str = readline("minishell$> ");
        add_history(str);
        if(!get_cmd())
            do_exec(buff);
    }

    return 0;
}