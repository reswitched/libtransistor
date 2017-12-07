LIBTRANSISTOR_HOME=../../
PROGRAM := ace
OBJ := main.o memory.o asm.o nro.o sha256.o http.o server.o

include $(LIBTRANSISTOR_HOME)/libtransistor.mk

all: $(PROGRAM).nro

%.o: %.c
	$(CC) $(CC_FLAGS) -Wno-pointer-arith -c -o $@ $<

%.o: %.S
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $@

$(PROGRAM).nro.so: ${OBJ} $(LIBTRANSITOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	$(LD) $(LD_FLAGS) -o $@ ${OBJ} $(LIBTRANSISTOR_NRO_LDFLAGS)

clean:
	rm -rf *.o *.nso *.nro *.so
