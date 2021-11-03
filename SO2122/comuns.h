
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define  SERVER_FIFO "balc_fifo"

#define  CLIENT_FIFO "pacient_%d_fifo"

#define TAM_MAX 50

typedef struct{//cliente -> servidor
 pid_t pid_pacient;
 char palavra[TAM_MAX];
}pacient_t;

typedef struct{//servidor -> cliente
  int pid;
 char palavra[TAM_MAX];
}balcao_t;
