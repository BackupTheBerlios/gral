# gral/measurement/test/corner-jacobian

PWD=$(shell pwd)
CONFIG=$(PWD)/../../local.config
include $(CONFIG)


SRC  =  $(shell ls *.C)
OBJ  =  $(SRC:%.C=%.o)
DEPS =  $(SRC:%.C=%.d)
EXEC =  test-corner-jacobian

include $(DEPS)

EXTRA_DEPMODULES+= gral/measurement gral/complex2d gral/cartesian3d geometry external-control

LIBS = -lgral-cartesian3d -lgral-complex2d -lgral-base\
       -lgeometry -lexternal-control -lutilities



new-check-clean: # new check clean1
	$(MAKE) new
	$(MAKE) check
	$(MAKE) clean

new : clean all


all : $(EXEC)


$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS) $(LIBS)

run:
	$(EXEC) 

check: run-check


clean: stdclean
	@rm -f $(EXEC)
	@rm -f *.o *~ *.flc core
	@rm -f .depend *.oogl *out 


