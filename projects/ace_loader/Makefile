LIBTRANSISTOR_HOME=../../
PROGRAM := ace
OBJ_BASE := main.o memory.o asm.o nro.o sha256.o http.o server.o
OBJ_JOKER := joker/joker.o joker/system.o joker/gfx.o joker/apps.o joker/ini.o joker/kfn.o joker/m_main.o joker/m_options.o joker/fonts.o
OBJ_GUI := ${OBJ_BASE} ${OBJ_JOKER}
OBJACE := build
OBJGUI := build_gui

include $(LIBTRANSISTOR_HOME)/libtransistor.mk

all: dirs $(OBJACE)/$(PROGRAM).nro $(OBJGUI)/$(PROGRAM).nro

dirs:
	mkdir $(OBJACE)
	mkdir $(OBJGUI)
	mkdir $(OBJGUI)/joker

$(OBJACE)/%.o: %.c
	$(CC) $(CC_FLAGS) -Wno-pointer-arith -c -o $@ $<

$(OBJACE)/%.o: %.S
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $@

$(OBJGUI)/%.o: %.c
	$(CC) $(CC_FLAGS) -DJOKER -Wno-pointer-arith -c -o $@ $<

$(OBJGUI)/%.o: %.S
	$(AS) $(AS_FLAGS) $< -filetype=obj -o $@

$(OBJACE)/$(PROGRAM).nro.so: $(OBJ_BASE:%.o=$(OBJACE)/%.o) $(LIBTRANSITOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	$(LD) $(LD_FLAGS) -o $@ $(OBJ_BASE:%.o=$(OBJACE)/%.o) $(LIBTRANSISTOR_NRO_LDFLAGS)

$(OBJGUI)/$(PROGRAM).nro.so: $(OBJ_GUI:%.o=$(OBJGUI)/%.o) $(LIBTRANSITOR_NRO_LIB) $(LIBTRANSISTOR_COMMON_LIBS)
	$(LD) $(LD_FLAGS) -o $@ $(OBJ_GUI:%.o=$(OBJGUI)/%.o) $(LIBTRANSISTOR_NRO_LDFLAGS)

clean:
	rm -rf $(OBJACE)
	rm -rf $(OBJGUI)

