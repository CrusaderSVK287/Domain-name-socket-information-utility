CC = gcc
CFLAGS = -Wall -Werror -std=gnu11 -g -DNDEBUG

SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/

BINNAME = dninfo

# Add arguments to be included in the program when making run or debug target
RUNARGS =

### COMPILATION ###

SRCS=$(wildcard $(SRCDIR)*.c)
OBJS=$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

BIN = $(BINDIR)$(BINNAME)
RUN = $(BIN) $(RUNARGS)

all: -setup $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)* $(BINDIR)*

### RUNNING APPLICATION ###

run: $(BIN)
	@./$(RUN)

debug: $(BIN)
	gdb --args ./$(RUN)

valgrind: $(BIN)
	valgrind -s --leak-check=full ./$(RUN)

### SET UP ###
-setup:
	@mkdir -p $(SRCDIR) $(OBJDIR) $(BINDIR)
