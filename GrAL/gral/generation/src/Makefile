CONFIG=$(shell pwd)/../local.config

include  $(CONFIG)

ifdef WITHTRIANGLE
TRIANGLEDIR = Triangle
SUBDIRS += $(TRIANGLEDIR)
endif

ifdef WITHGRUMMP
GRUMMPDIR = Grummp 
SUBDIRS += $(GRUMMPDIR)
endif

include  $(RECURSIVETARGETS)




