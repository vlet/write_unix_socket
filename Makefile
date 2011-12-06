DESTDIR =
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
RUNTIMEDIR = /var/run
SOCK_PATH = $(RUNTIMEDIR)/mon/snmptrap

CFLAGS = -Wall -DSOCK_PATH='"$(SOCK_PATH)"'
LDFLAGS =
LIBS =

BIN = write_unix_socket

all: $(BIN)

$(BIN): $(BIN).o

$(BIN).o: $(BIN).c

install: $(BIN)
	mkdir -p $(DESTDIR)$(BINDIR) && \
	install -m755 $(BIN) $(DESTDIR)$(BINDIR)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(BIN)

clean:
	rm -f $(BIN) $(BIN).o
