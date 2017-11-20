LIBTRANSISTOR_HOME=../../

include $(LIBTRANSISTOR_HOME)/libtransistor.mk

all: example.nro

example.nro.so: example.o $(LIBTRANSITOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	$(LD) $(LD_FLAGS) -o $@ $< $(LIBTRANSISTOR_NRO_LDFLAGS)
