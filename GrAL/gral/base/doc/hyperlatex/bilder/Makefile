

PSTRICKS=$(shell ls *.tex)
EPSFILES:=$(PSTRICKS:%.tex=%.eps)
GIFFILES=$(PSTRICKS:%.tex=%.gif)
JPGFILES=$(PSTRICKS:%.tex=%.jpeg)


CONVERT = convert 
#CONVERT = pstogif

.SUFFIXES: .gif .eps .ps .tex .jpeg

.tex.eps:
	latex $<  && dvips -Pamz -Pcmz -E ${<:%.tex=%.dvi} -o $@

#.eps.gif:
#	$(CONVERT) $< $@

# convert 5.2.6 on sun makes {gif|jpeg}.{0|1} ?!

.eps.gif:
	$(CONVERT) $< $@
	mv ${@}.0 $@
	rm -r ${@}.1

.eps.jpeg:
	echo $(CONVERT)
	$(CONVERT) $< $@
	mv ${@}.0 $@ || echo " (OK) "
	rm -f ${@}.1

# ?????
#cell-on-cell.jpeg: cell-on-cell.ps
#	pstogif  cell-on-cell.ps cell-on-cell.gif
#	convert  cell-on-cell.gif cell-on-cell.jpeg

#cell-on-cell.eps: stop-sign.eps
#cell-on-cell.ps: stop-sign.eps

all: stop-sign.eps $(JPGFILES)

eps: stop-sign.eps $(EPSFILES)

clean:
	rm -f  *.aux *.log *.dvi *~ 

realclean: clean
	rm -f $(JPGFILES) $(GIFFILES) $(EPSFILES)
