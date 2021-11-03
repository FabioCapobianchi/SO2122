
#include "comuns.h"
#include <signal.h>

#define NPALAVRAS 7

int b_fifo_fd;
int p_fifo_fd;


int main(int argc, char **argv){

pacient_t pacient;
balcao_t balc;

int res;
//char b_fifo_fname[50];
char p_fifo_fname[50];
//char * aux;
printf("/nBalcao de atendimento/n");
res = mkfifo(SERVER_FIFO, 0777);
if (res == -1){
perror("\nmkfifo do FIFO Balcao deu erro");
exit(EXIT_FAILURE);
}
fprintf(stderr, "\nFIFO Balcao criado");


b_fifo_fd = open(SERVER_FIFO, O_RDWR);
if (b_fifo_fd == -1){
perror("\nmkErro ao abrir FIFO balcao(RDWR/blocking)");
exit(EXIT_FAILURE);
}
 fprintf(stderr, "\nFIFO Balcao aberto para READ (+WRITE) bloqueante");

 memset(pacient.palavra, '\0', TAM_MAX);

 while (1){

 res = read(b_fifo_fd, & pacient, sizeof(pacient));
 if(res < sizeof(pacient)){
   fprintf(stderr,"\nRecebida mensagem incompleta " "[bytes lidos: %d]", res);
   continue;
 }

 fprintf(stderr,"\nRecebido %s", pacient.palavra);

  if(!strcasecmp(pacient.palavra, "fimb")){

  close(b_fifo_fd);
    unlink(SERVER_FIFO);
    exit(EXIT_SUCCESS);

  }

   strcpy(balc.palavra,pacient.palavra);
   balc.pid = pacient.pid_pacient;
   fprintf(stderr, "\nbalcao %s", balc.palavra);

  sprintf(p_fifo_fname, CLIENT_FIFO, pacient.pid_pacient);

  p_fifo_fd = open(p_fifo_fname, O_WRONLY);

  if(p_fifo_fd == -1)
    perror("\Erro no open - Ninguem quis a resposta");
    else{
      fprintf(stderr, "\nFIFO cliente aberto para WRITE");

    res = write(p_fifo_fd, & balc, sizeof(balc));
    if(res == sizeof(balc))
      fprintf(stderr,"\nescreveu ao cliente %s\n",pacient.palavra);
      else
      perror("\nerro a escrever a balcao");

    close(p_fifo_fd);
    fprintf(stderr,"\nFIFO cliente fechado");
    }

 }
 close(b_fifo_fd);
 unlink(SERVER_FIFO);

 return 0;
 }
