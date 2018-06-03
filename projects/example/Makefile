TARGET := example
OBJECTS := example.o

NRO_ICON		:=	icon.jpg
NRO_NAME		:=	Example Application
NRO_DEVELOPER	:=	Example Developer

all: $(TARGET).nro $(TARGET).nso

clean:
	rm -f *.o *.nro *.nso *.so

# include libtransistor rules
ifndef LIBTRANSISTOR_HOME
    $(error LIBTRANSISTOR_HOME must be set)
endif
include $(LIBTRANSISTOR_HOME)/libtransistor.mk

$(TARGET).nro.so: $(OBJECTS) $(LIBTRANSITOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	$(LD) $(LD_FLAGS) -o $@ $(OBJECTS) $(LIBTRANSISTOR_NRO_LDFLAGS)

$(TARGET).nso.so: $(OBJECTS) $(LIBTRANSITOR_NSO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	$(LD) $(LD_FLAGS) -o $@ $(OBJECTS) $(LIBTRANSISTOR_NSO_LDFLAGS)
