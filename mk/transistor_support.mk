# LIBTRANSISTOR SUPPORT
#  Headers that aren't really part of libtransistor, but
#  are needed to build our libraries, and tools/link scripts
#  needed to pass build environment tests.

libtransistor_SUPPORT_HEADERS := machine/_align.h sys/_iovec.h sys/socket.h sys/_sockaddr_storage.h sys/sockio.h netinet/in.h netinet/tcp.h netdb.h arpa/inet.h net/if.h sys/features.h nl_types.h lz4.h netinet6/in6.h features.h expected.hpp

DIST_TRANSISTOR_SUPPORT := $(addprefix $(LIBTRANSISTOR_HOME)/include/,$(libtransistor_SUPPORT_HEADERS)) \
	$(LIBTRANSISTOR_HOME)/libtransistor.mk \
	$(LIBTRANSISTOR_HOME)/link.T \
	$(LIBTRANSISTOR_HOME)/fs.T\
	$(LIBTRANSISTOR_HOME)/tools/elf2nxo.py

$(LIBTRANSISTOR_HOME)/libtransistor.mk: libtransistor.mk
	install $< $@

$(LIBTRANSISTOR_HOME)/link.T: link.T
	install $< $@

$(LIBTRANSISTOR_HOME)/fs.T: fs.T
	install $< $@

$(LIBTRANSISTOR_HOME)/tools/elf2nxo.py: tools/elf2nxo.py
	install -d $(@D)
	install $< $@

$(LIBTRANSISTOR_HOME)/include/%: $(SOURCE_ROOT)/include/%
	install $< $@

.PHONY: dist_transistor_support
dist_transistor_support: $(DIST_TRANSISTOR_SUPPORT)
