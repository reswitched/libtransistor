# Neither

neither_HEADER_NAMES := either.hpp lift.hpp maybe.hpp neither.hpp traits.hpp try.hpp

DIST_NEITHER_HEADERS := $(addprefix $(LIBTRANSISTOR_HOME)/include/neither/,$(neither_HEADER_NAMES))

$(LIBTRANSISTOR_HOME)/include/neither/%: $(SOURCE_ROOT)/neither/neither/include/%
	install -d $(@D)
	install $< $@

.PHONY: dist_neither_headers
dist_neither_headers: $(DIST_NEITHER_HEADERS)
