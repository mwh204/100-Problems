program_NAME := roguelike
program_C_SRCS := $(wildcard *.c)
program_OBJS := ${program_C_SRCS:.c=.o}
program_LIBRARIES := ncurses

CFLAGS := -Wall -O2
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

.PHONY: all clean distclean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean
