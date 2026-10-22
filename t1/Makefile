CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = scheduler
SRC = escalonador.c escalonador_io.c fila.c
HDR = escalonador_io.h fila.h

all: $(TARGET)

$(TARGET): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

zip: clean
	zip -r ../t1-so-solucao.zip .

.PHONY: all clean zip
