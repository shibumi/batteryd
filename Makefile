CC=gcc

LDFLAGS= $(shell pkg-config --cflags --libs libnotify)


PREFIX=/usr
BINDIR=${PREFIX}/bin
INSTALLDIR=${DESTDIR}${BINDIR}

SOURCE := batteryd.c
TARGET := batteryd

all: ${TARGET}

${TARGET}: ${SOURCE}
	@echo ${CC} $^ -o $@
	@${CC} $^ -o $@  ${LDFLAGS}

install: 
	install -d ${INSTALLDIR}
	install -m 755 ${TARGET} ${INSTALLDIR}/${TARGET}

clean: 
	${RM} ${TARGET}

.PHONY: clean
