CC=gcc
CFLAGS=-Wall -std=c99 -g -O2 -I./include
LDFLAGS=
OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
VSSRCDIR=./src/aesavs
TESTDIR=./tests
INCDIR=./include

OBJS=$(OBJDIR)/main.o

TARGET=$(BINDIR)/a.out

.PHONY: all clean dir rebuild

all: dir $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $@

-include $(OBJS:.o=.d)

clean:
	rm -f $(OBJS) $(TARGET) $(OBJDIR)/*.d
	# @echo "Removing AESAVS files ..."
	# rm -rf $(KATFILES_TO_DELETE)
	# @echo "AESAVS files removal completed  successfully."

dir:
	@mkdir -p $(OBJDIR) $(BINDIR)

rebuild: clean all

leak: 
	(cd bin && valgrind --leak-check=full --show-leak-kinds=all ./a.out)