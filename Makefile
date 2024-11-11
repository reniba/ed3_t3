CC          := g++
DEBUG_FLAGS := #-g3 -pedantic -Werror=implicit-function-declaration -fsanitize=address,undefined
FLAGS       :=# -Wall -Werror $(DEBUG_FLAGS)

SRC         := ./src
SRC_2  		:= ./src/funcionalities
BIN         := ./bin
HEADERS     := ./headers
EXEC        := prog
ZIP         := exercicio.zip

# List of all expected $(BIN)/*.o
ALL_SRC     := $(wildcard $(SRC)/*.c)
ALL_SRC_2   := $(wildcard $(SRC_2)/*.c)
ALL_SRC_3   := $(wildcard $(SRC)/*.cpp)
ALL_SRC_4   := $(wildcard $(SRC_2)/*.cpp)
ALL         := $(ALL_SRC:$(SRC)/%.c=$(BIN)/%.o) $(ALL_SRC_2:$(SRC_2)/%.c=$(BIN)/%.o) $(ALL_SRC_3:$(SRC)/%.cpp=$(BIN)/%.o) $(ALL_SRC_4:$(SRC_2)/%.cpp=$(BIN)/%.o)


all: $(EXEC)

run:
	./$(EXEC)

clean:
	rm -f $(EXEC) $(BIN)/*.o

zip:
	rm -f $(ZIP)
	zip $(ZIP) Makefile $(HEADERS)/*.h $(SRC)/*.c $(SRC_2)/*.c $(SRC)/*.cpp $(SRC_2)/*.cpp


$(EXEC): $(ALL)
	$(CC) -o $(EXEC) $(ALL) $(FLAGS)

$(BIN)/%.o: $(SRC)/%.c $(BIN)
	$(CC) -o $@ -c $< -I $(HEADERS) $(FLAGS)

# Rule for files in SRC_2
$(BIN)/%.o: $(SRC_2)/%.c $(BIN)
	$(CC) -o $@ -c $< -I $(HEADERS) $(FLAGS)

$(BIN)/%.o: $(SRC)/%.cpp $(BIN)
	$(CC) -o $@ -c $< -I $(HEADERS) $(FLAGS)

# Rule for files in SRC_2
$(BIN)/%.o: $(SRC_2)/%.cpp $(BIN)
	$(CC) -o $@ -c $< -I $(HEADERS) $(FLAGS)

$(BIN):
	mkdir -p $(BIN)
