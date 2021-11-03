all:
	gcc -g -Wall -o balcao balcao.c
	gcc -g -Wall -o paciente paciente.c

servidor:
	gcc -c balcao.c
clififo:
	gcc -c paciente.c

clean:
	$(RM) balcao balcao.o
	$(RM) paciente paciente.o
