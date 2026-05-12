# Nome do compilador e opções
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -O2 -fPIE -fstack-protector-strong
LDFLAGS = -fPIE

# Arquivos fonte e objeto
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Nome do executável gerado
TARGET = xadrez
ifeq ($(OS),Windows_NT)
    TARGET = xadrez.exe
    RM = del /Q
else
    RM = rm -f
endif

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