program=test
OBJ = joker.o system.o gfx.o apps.o ini.o kfn.o fonts.o m_main.o m_options.o
LIBS = -lm -lSDL

OPT=-g
CC=gcc
CFLAGS=${OPT} -DLINUX

build: ${program}

clean:
	rm -f *.o ${program}

${program}: ${OBJ}
	${CC} ${OBJ} ${LIBS} -o ${program} ${OPT}

