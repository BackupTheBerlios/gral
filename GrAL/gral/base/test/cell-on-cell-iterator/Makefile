# gral/base/test/cell-on-cell-iterator

PWD=$(shell pwd)
CONFIG=$(PWD)/../../mk.config
include $(CONFIG)


LOCALSOURCES =  $(shell ls *.C)
LOCALOBJECTS =  $(LOCALSOURCES:%.C=%.o)
DEPS = $(LOCALSOURCES:%.C=%.d)
TARGETS = test-cell-on-cell-iterator
EXEC =  $(TARGETS)

include $(DEPS)

DEPMODULES+= gral/cartesian2d gral/complex2d \
             gral/testing geometry

LIBS = -lgral-cartesian2d  -lgral-complex2d \
       -lgral-base -lgeometry



new-check-clean: new check clean

new : clean all


all : $(TARGETS)


test-cell-on-cell-iterator: $(LOCALOBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS) $(LOCALOBJECTS) $(LDFLAGS) $(LIBS)

run:
	$(EXEC) 

check:
	./runtest ./$(EXEC)

clean: stdclean
	rm -f $(EXEC)
	rm -f *.o *~ *.flc core
	rm -f .depend *.oogl *.out 

