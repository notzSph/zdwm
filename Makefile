# zDwm - zSph Dynamic Window Manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c zdwm.c util.c
OBJ = ${SRC:.c=.o}

all: zdwm

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

zdwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f zdwm ${OBJ} zdwm-${VERSION}.tar.gz

dist: clean
	mkdir -p zdwm-${VERSION}
	cp -R LICENSE Makefile README.md config.def.h config.mk\
		zzdwm.1 drw.h util.h ${SRC} transient.c zdwm-${VERSION}
	tar -cf zdwm-${VERSION}.tar zdwm-${VERSION}
	gzip zdwm-${VERSION}.tar
	rm -rf zdwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f zdwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/zdwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < zdwm.1 > ${DESTDIR}${MANPREFIX}/man1/zdwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/zdwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/zdwm\
		${DESTDIR}${MANPREFIX}/man1/zdwm.1

.PHONY: all clean dist install uninstall
