objdir := build
executable := aash

SRC := $(wildcard *.c)
OBJ := $(addprefix $(objdir)/, $(SRC:.c=.o))

all: $(executable)

$(executable): $(OBJ)
	@echo "[LD] $@"
	@$(CC) $(LDFLAGS) -o $@ $^

$(objdir)/%.o: %.c
	@mkdir -p $(@D)
	@echo "[CC] $@"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(executable) $(OBJ)

run: $(executable)
	./$(executable)

