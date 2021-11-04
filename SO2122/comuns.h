
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define  BALC_FIFO "balc_fifo"
#define  CLIENT_FIFO "utent_%d_fifo"
#define  MEDIC_FIFO "medic_%d_fifo"

#define  TAM_MAX 50
#define  SINT_MAX 8

typedef struct{//cliente -> servidor
 pid_t pid_utent;
 char nome[TAM_MAX];
 char palavra[TAM_MAX];
}utent_t;

typedef struct{//servidor -> cliente
  int pid;
  char pnome[TAM_MAX];
  char palavra[TAM_MAX];

}balcao_t;

typedef struct{
  pid_t pid_medic;
  char mnome[TAM_MAX];
  char espec[TAM_MAX];
  char unome[TAM_MAX];
  char pr[TAM_MAX];
}medic_t;
