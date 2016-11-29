TARGET= aagaProject

SRCDIR= ./src
OBJDIR= ./obj
LIBDIR= ./lib
BINDIR = ./bin

CC = gcc
CFLAGS = -Wall -Wextra -Wimplicit -std=c11 

LINKER = gcc -o
LFLAGS = -Wall

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

rm = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS) 2>>log 
	@echo "\033[32mLinking complete!\033[39m"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ 2>>log
	@echo "\033[33mCompiled "$<" successfully!\033[39m"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "\033[32mCleanup complete!\033[39m"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "\033[31mExecutable removed!\033[39m"
