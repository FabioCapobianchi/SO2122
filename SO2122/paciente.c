
#include "comuns.h"
#include <signal.h>


int main(){

int b_fifo_fd;
int p_fifo_fd;
pacient_t pacient;
balcao_t balc;
char p_fifo_fname[25];
int read_res;

//Cria o FIFO do Paciente
pacient.pid_pacient = getpid();
sprintf(p_fifo_fname, CLIENT_FIFO, pacient.pid_pacient);

if(mkfifo(p_fifo_fname, 0777) == -1){
perror("\nmkfifo do FIFO Paciente deu erro");
exit(EXIT_FAILURE);
}

fprintf(stderr,"\nFIFO do Paciente criado");

b_fifo_fd = open(SERVER_FIFO, O_WRONLY);
if(b_fifo_fd == -1){
 fprintf(stderr, "\nO Balcao não esta a correr\n");
 unlink(p_fifo_fname);
 exit(EXIT_FAILURE);
}
 fprintf(stderr,"\nFIFO do Balcao aberto WRITE / BLOCKING");
 //
 //
 //
 //
 p_fifo_fd = open(p_fifo_fname, O_RDWR);
 if(p_fifo_fd == -1){
 perror("\nErro ao abrir o FIFO do Paciente");
 close(p_fifo_fd);
 unlink(p_fifo_fname);
 exit(EXIT_FAILURE);
 }


 fprintf(stderr, "\nFIFO do Paciente aberto para READ(+Write) Block");

 memset(pacient.palavra, '\0', TAM_MAX);

 while(1){

printf("\nNome> ");
scanf("%s",pacient.palavra);
if(!strcasecmp(pacient.palavra,"fim" || !strcasecmp(pacient.palavra,"fimb"))){
write(b_fifo_fd, &pacient, sizeof(pacient));
break;
}
// B) Envia ao balcao
write(b_fifo_fd, &pacient, sizeof(pacient));

// c) recebe do balcao//////////////////////////////////

read_res = read(p_fifo_fd, &balc, sizeof(balc));
if(read_res == sizeof(balc))
  printf("\nNome -> %s PID -> %d" , balc.palavra,balc.pid);
else
  printf("\nSem resposta do balcao" "[bytes lidos: %d]", read_res);
}

close(p_fifo_fd);
close(b_fifo_fd);
unlink(p_fifo_fname);
return 0;

}
