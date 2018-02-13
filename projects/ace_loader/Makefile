LIBTRANSISTOR_HOME=../../
LIBNRO_SERVER_OBJ := nro.o sha256.o http.o server.o common_setup.o common_memory.o
LIBNRO_SERVER := libnro_server.a
WK_ACE_OBJ := wk_main.o wk_memory.o wk_asm.o
SYSMOD_ACE_OBJ := sysmod_main.o sysmod_memory.o

include $(LIBTRANSISTOR_HOME)/libtransistor.mk

all: $(LIBNRO_SERVER) wk_ace.nro sysmod_ace.nro

$(LIBNRO_SERVER): $(LIBNRO_SERVER_OBJ)
	rm -f $@
	$(AR) rcs $@ $+

%.o: %.c
	$(CC) $(CC_FLAGS) -Wno-pointer-arith -c -o $@ $<

%.o: %.S
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $@

wk_ace.nro.so: $(WK_ACE_OBJ) $(LIBNRO_SERVER) $(LIBTRANSITOR_NRO_DEPS)
	$(LD) $(LD_FLAGS) -o $@ $(WK_ACE_OBJ) $(LIBNRO_SERVER) $(LIBTRANSISTOR_NRO_LDFLAGS)

sysmod_ace.nro.so: $(SYSMOD_ACE_OBJ) $(LIBNRO_SERVER) $(LIBTRANSITOR_NRO_DEPS)
	$(LD) $(LD_FLAGS) -o $@ $(SYSMOD_ACE_OBJ) $(LIBNRO_SERVER) $(LIBTRANSISTOR_NRO_LDFLAGS)

clean:
	rm -rf *.o *.nso *.nro *.so
