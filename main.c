// Получить команду ввода 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#define  MAX_CMD  1024
char buff[MAX_CMD];
// Размер буфера командной строки 1024 байта
int get_cmd()
{
	memset(buff, 0x00, MAX_CMD);
	printf("[lee@localhost ~]$ ");
	fflush(stdout);
	// Отображение аналогового терминала
	
	fgets(buff, MAX_CMD - 1, stdin);
	//войти
	buff[strlen(buff) - 1] = '\0';
	// Последняя цифра \ 0
	return 0;
}

// Разобрать входную команду

char **do_parse(char *buff)
{
	char *ptr = buff;
	int argc = 0;
	static char *argv[32];
	// Сохраняем все извлеченные команды в argv, потому что они используются во всей жизненной области программы и объявлены как статические
	
	while('\0' != *ptr)
	{
		if(' ' != *ptr)
		{
			argv[argc++] = ptr;
			while('\0' != *ptr && ' ' != *ptr)
			{
				ptr++;
			}
			*ptr = '\0';
		}
		ptr++;
	}
	// Удаляем пробелы и извлекаем команды

	argv[argc] = NULL;
	// Последняя цифра должна быть NULL
	return argv;
}

// Перенаправление вывода

void do_redirect(char *buff)
{
	int redirect_flag = 0;
	// Запись> Количество вхождений
	char *redirect_file = NULL;
	char *ptr = buff;

	while(*ptr != '\0')
	{
		if(*ptr == '>')
		{
			*ptr++ = '\0';
			++redirect_flag;
			// Если этот бит>, счетчик увеличивается на единицу, и этот бит переписывается как \ 0, чтобы предотвратить его интерпретацию как команду

			if(*ptr == '>')
			{
				++redirect_flag;
				ptr++;
			}
			
			while(*ptr == ' ' && *ptr != '\0')
			{
				ptr++;
			}

			redirect_file = ptr;
			// После обнаружения >> следующее имя перенаправленного файла, которое будет проанализировано
			
			while(*ptr != ' ' && *ptr != '\0')
			{
				ptr++;
			}				
			*ptr = '\0';
		}
		ptr++;
	}
	if(redirect_flag == 1)
	{
		int fd = open(redirect_file, O_WRONLY|O_CREAT|O_TRUNC, 0664);
		dup2(fd, 1);
		// Перенаправляем стандартный вывод в файл
		// Если появляется только один>, это означает, что это перенаправление перезаписи, открыто в режиме перезаписи O_TRUNC
	}
	else if(redirect_flag == 2)
	{
		int fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0664);
		dup2(fd, 1);
		//> Появляется дважды, указывая, что это дополнительное перенаправление, открытое в режиме добавления O_APPEND
	}
}