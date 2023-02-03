CC = gcc
CFLAGS = -Wall -Werror -std=gnu11 -g

SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/

BINNAME = dminfo

# Add arguments to be included in the program when making run target
RUNARGS =

SRCS=$(wildcard $(SRCDIR)*.c)
OBJS=$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

BIN = $(BINDIR)$(BINNAME)

all: -setup $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)* $(BINDIR)*

### RUNNING APPLICATION ###

run: $(BIN)
	@./$(BIN) $(RUNARGS)

debug: $(BIN)
	gdb --args ./$(BIN) $(RUNARGS)

valgrind: $(BIN)
	valgrind -s --leak-check=full ./$(BIN) $(RUNARGS)

### SET UP ###
-setup:
	@mkdir -p $(SRCDIR) $(OBJDIR) $(BINDIR)

### RELEASE ###
release: CFLAGS += -DNDEBUG
release: $(BIN)
