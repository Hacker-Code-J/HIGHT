CC=gcc
CFLAGS=-Wall -std=c99 -g -O2 -I./include
LDFLAGS=
OBJDIR=./obj
BINDIR=./bin
SRCDIR=./src
TESTDIR=./tests
INCDIR=./include

OBJS=$(OBJDIR)/hight_core.o $(OBJDIR)/hight_utils.o \
	$(OBJDIR)/main.o

TARGET=$(BINDIR)/a.out

.PHONY: all clean dir rebuild

all: dir $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# $(OBJDIR)/main.o: main.c
# 	$(CC) $(CFLAGS) -MMD -MP -c main.c -o $@

-include $(OBJS:.o=.d)

# $(OBJDIR)/hight_core.o: $(SRCDIR)/hight_core.c $(INCDIR)/hight.h
# $(OBJDIR)/hight_utils.o: $(SRCDIR)/hight_utils.c $(INCDIR)/hight_utils.h

clean:
	rm -f $(OBJS) $(TARGET) $(OBJDIR)/*.d
#	@echo "Removing AESAVS files ..."
#	rm -rf $(KATFILES_TO_DELETE)
#	@echo "AESAVS files removal completed  successfully."

dir:
	@mkdir -p $(OBJDIR) $(BINDIR)

rebuild: clean all

run:
	(cd bin && ./a.out)

leak: 
	(cd bin && valgrind --leak-check=full --show-leak-kinds=all ./a.out)

comp:
	(cd bin && ./a.out > speed.txt)
	(cd bin && mv speed.txt ../view/)
	(cd view && python3 compare.py)