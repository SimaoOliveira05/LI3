CC= gcc
CFLAGS= -Wall -Wextra $(shell pkg-config glib-2.0 --cflags) -Iinclude -I./recomendador -g -O3
LDFLAGS= $(shell pkg-config glib-2.0 --libs) -lncurses -lm

# Detectar o sistema operacional
UNAME_S := $(shell uname -s)

# Selecionar o arquivo objeto correto com base no sistema operacional
ifeq ($(UNAME_S),Linux)
    RECOMMENDER_OBJECT = ./recomendador/recomendador-linux-x86_64.o
endif
ifeq ($(UNAME_S),Darwin)
    RECOMMENDER_OBJECT = ./recomendador/recomendador-macos-x86_64.o
endif
ifeq ($(UNAME_S),Windows)
    RECOMMENDER_OBJECT = ./recomendador/recomendador-arm64.o
endif


# Fontes comuns
COMMON_SOURCES = $(shell find ./src -name "*.c" \
    -not -path "./src/main.c" \
    -not -path "./src/tests/*" \
    -not -path "./src/interactive/interactive.c" \
    -not -path "./src/interactive/mainInteractive.c")
COMMON_OBJECTS = $(COMMON_SOURCES:.c=.o)

# Fontes do programa principal
MAIN_SOURCE = ./src/main.c
MAIN_OBJECT = $(MAIN_SOURCE:.c=.o)
TARGET = programa-principal

# Fonte do programa Interativo
INTERACTIVE_SOURCES = ./src/interactive/interactive.c ./src/interactive/mainInteractive.c
INTERACTIVE_OBJECTS = $(INTERACTIVE_SOURCES:.c=.o)
INTERACTIVE_TARGET = programa-interativo

# Fontes dos testes
TEST_SOURCES = ./src/tests/maintest.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)
TEST_TARGET = programa-testes

all: $(TARGET) $(TEST_TARGET) $(INTERACTIVE_TARGET)

$(INTERACTIVE_TARGET): $(COMMON_OBJECTS) $(INTERACTIVE_OBJECTS) $(RECOMMENDER_OBJECT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET): $(COMMON_OBJECTS) $(MAIN_OBJECT) $(RECOMMENDER_OBJECT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(COMMON_OBJECTS) $(TEST_OBJECTS) $(RECOMMENDER_OBJECT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean-results:
	rm -f resultados/*.txt resultados/*.csv

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(INTERACTIVE_TARGET) $(COMMON_OBJECTS) $(MAIN_OBJECT) $(TEST_OBJECTS) $(INTERACTIVE_OBJECTS) resultados/*.txt resultados/*.csv
