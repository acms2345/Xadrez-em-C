# Nome do compilador e opções
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -O2 -fPIE -fstack-protector-strong
LDFLAGS = -fPIE

# Arquivos fonte e objeto
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(filter-out teste.c, $(SRCS)))
TEST_SRCS = $(filter-out menu.c, $(SRCS))
TEST_OBJS = $(patsubst %.c, %.o, $(filter-out menu.c, $(SRCS))) teste.o

# Nome do executável gerado
TARGET = xadrez
TARGET_TEST = xadrez_teste

ifeq ($(OS),Windows_NT)
    TARGET = xadrez.exe
    TARGET_TEST = xadrez_teste.exe
    RM = del /Q
else
    RM = rm -f
endif


# Alvo padrão
all: $(TARGET)

# Compilação do executável a partir dos objetos
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


$(TARGET_TEST): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^



# Compilação dos arquivos objeto a partir dos fontes
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)


test: $(TARGET_TEST)

# Compilação do executável a partir dos objetos

# Alvo padrão para evitar erros caso o nome do arquivo coincida com nomes de comando (e.g. clean)
.PHONY: all test clean