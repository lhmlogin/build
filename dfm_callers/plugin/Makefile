INCLUDES   =  -I./include

SOFLAGS = -fPIC -shared
# CFLAGS  = -Wall
CFLAGS  = 
#DEBUG   =  -g3
DEBUG   =
CC = gcc

CCSRCS	= $(wildcard *.c)
CCOBJS = $(patsubst %.c,%.so, $(CCSRCS))

all:$(CCOBJS)
#compile
$(CCOBJS): %.so: %.c
	# $(info target:$@)
	# $(info first:$<)
	# $(info all:$(CCOBJS))
	$(CC) -fPIC $(INCLUDES) $(CFLAGS) $(DEBUG) -ldl -c $< -o $@
	/incampro/release/bin/dfm_brand $@

