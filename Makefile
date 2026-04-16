# Makefile para Trabalho1_SisOP
# Compilador e flags
CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lpthread

# Diretórios
SRC_DIR = src
BIN_DIR = src

# Executáveis
PROCESS_COUNTER = $(BIN_DIR)/process_counter
THREADS_COUNTER = $(BIN_DIR)/threads_counter

# Arquivos fonte
PROCESS_SRC = $(SRC_DIR)/process_counter.c
THREADS_SRC = $(SRC_DIR)/threads_counter.c

# Targets
.PHONY: all clean help rebuild

# Target padrão
all: $(PROCESS_COUNTER) $(THREADS_COUNTER)

# Compilar process_counter
$(PROCESS_COUNTER): $(PROCESS_SRC)
	@echo "Compilando process_counter..."
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
	@echo "✓ process_counter compilado com sucesso"

# Compilar threads_counter
$(THREADS_COUNTER): $(THREADS_SRC)
	@echo "Compilando threads_counter..."
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
	@echo "✓ threads_counter compilado com sucesso"

# Limpar executáveis
clean:
	@echo "Limpando executáveis..."
	rm -f $(PROCESS_COUNTER) $(THREADS_COUNTER)
	@echo "✓ Limpeza concluída"

# Rebuild: limpar e recompilar tudo
rebuild: clean all

# Executar process_counter com 4 processos
run-process:
	@echo "Executando process_counter com 4 processos (tipo 2 - com semáforo)..."
	time $(PROCESS_COUNTER) 4 2

# Executar threads_counter com 4 threads
run-threads:
	@echo "Executando threads_counter com 4 threads (tipo 2 - com mutex)..."
	time $(THREADS_COUNTER) 4 2

# Executar ambos
run-all: run-process run-threads

# Ajuda
help:
	@echo "Targets disponíveis:"
	@echo "  make             - Compila ambos os programas (padrão)"
	@echo "  make clean       - Remove executáveis"
	@echo "  make rebuild     - Limpa e recompila tudo"
	@echo "  make run-process - Executa process_counter"
	@echo "  make run-threads - Executa threads_counter"
	@echo "  make run-all     - Executa ambos os programas"
	@echo "  make help        - Mostra esta mensagem"
