all: tp2

tp2: 	tp2.c Renderizador.o Grafo.o
	gcc tp2.c Renderizador.o Grafo.o -lm -o tp2


Renderizador.o:	Renderizador.c Renderizador.h
		gcc -c Renderizador.c

Grafo copy.o: 	Grafo.c Grafo.h
		gcc -c Grafo.c

clean:
	rm tp2
	rm Renderizador.o
	rm Grafo.o
