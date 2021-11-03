
#include "comuns.h"
#include <signal.h>

#define NPALAVRAS 7

int b_fifo_fd;
int p_fifo_fd;


int main(int argc, char **argv){

utent_t utent;
balcao_t balc;

int res;
//char b_fifo_fname[50];
char p_fifo_fname[50];
char* sint[SINT_MAX][2]={
{"colica",  "estomatologia"},
{"nauseas",  "estomatologia"},
{"cefaleia",  "medicina geral"},
{"dor de cabeca",  "medicina geral"},
{"febre", "medicina geral"},
{"visao",  "oftalmologista"},
{"ouvido",  "otorrino"},
{"lesao",  "ortopedista"}
};

fprintf(stdout,"\nBalcao de atendimento\n");
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

 memset(utent.palavra, '\0', TAM_MAX);

 while (1){

 res = read(b_fifo_fd, & utent, sizeof(utent));
 if(res < sizeof(utent)){
   fprintf(stderr,"\nRecebida mensagem incompleta " "[bytes lidos: %d]", res);
   continue;
 }

 fprintf(stderr,"\nRecebido de %s sintoma %s",utent.nome, utent.palavra);

  if(!strcasecmp(utent.palavra, "fimb")){

  close(b_fifo_fd);
    unlink(SERVER_FIFO);
    exit(EXIT_SUCCESS);

  }
  if(!strcasecmp(utent.palavra, "fim")){
    close(p_fifo_fd);
    fprintf(stderr,"\nFIFO utente %s fechado\n",utent.nome);

  }

   strcpy(balc.palavra,utent.palavra);
   strcpy(balc.pnome,utent.nome);
   balc.pid = utent.pid_utent;
   fprintf(stderr, "\nutente %s sintoma %s\n",balc.pnome, balc.palavra);

  sprintf(p_fifo_fname, CLIENT_FIFO, utent.pid_utent);

  p_fifo_fd = open(p_fifo_fname, O_WRONLY);

  if(p_fifo_fd == -1)
    perror("\Erro no open - Ninguem quis a resposta");
    else{
      fprintf(stderr, "\nFIFO utente aberto para WRITE");
/////////////////////////////

      for(int i=0;i<SINT_MAX;i++){
        if(!strcasecmp(utent.palavra,sint[i][0])){
           strcpy(balc.palavra,sint[i][1]);
           break;
        }else{
          strcpy(balc.palavra,"Sintoma Desconhecido");
        }
      }
///////////////////////////////////

    res = write(p_fifo_fd, & balc, sizeof(balc));
    if(res == sizeof(balc))
      fprintf(stderr,"\nescreveu ao utente %s\n",utent.palavra);
      else
      perror("\nerro a escrever ao utente");

    close(p_fifo_fd);
    fprintf(stderr,"\nFIFO utente fechado\n");
    }

 }
 close(b_fifo_fd);
 unlink(SERVER_FIFO);

 return 0;
 }
