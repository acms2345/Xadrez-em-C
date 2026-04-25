# Nome do compilador e opções
CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -O2

# Arquivos fonte e objeto
SRCS = menu.c jogo.c jogadasvalidas.c traducao.c
OBJS = $(SRCS:.c=.o)

# Nome do executável gerado
TARGET = xadrez

# Alvo padrão
all: $(TARGET)

# Compilação do executável a partir dos objetos
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação dos arquivos objeto a partir dos fontes
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Alvo padrão para evitar erros caso o nome do arquivo coincida com nomes de comando (e.g. clean)
.PHONY: all clean