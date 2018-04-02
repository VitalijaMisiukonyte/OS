CFLAGS = -g -Wall
C_FILES = $(wildcard ./*.c)

all: ${C_FILES} 
	gcc ${CFLAGS} -o musu-os ${C_FILES}

clean: 
	-rm -f musu-os
