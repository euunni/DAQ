FILENAME = programmer_ibs_sipm_daq

EXE	=	$(FILENAME).exe

CC	=	gcc

COPTS	=	-fPIC -Wall

FLAGS	=	-shared -Wall,-soname -nostartfiles -s

LDFLAGS =        -O2 -Wall 

OutPutOpt = -o 

LIBS	=	-L$(NKHOME)/lib -lNoticeIBS_SIPM_DAQ -lm

INCLUDEDIR =	-I$(NKHOME)/include

INSTALLDIR     =	$(NKHOME)/bin
INSTALLINCLUDE =	$(NKHOME)/include

OBJS	=	$(FILENAME).o

INCLUDES =	 

#########################################################################

all	:	$(EXE)
clean	:
		/bin/rm -f $(OBJS) $(EXE)

install	:	$(EXE)
		#/bin/rm -f $(INSTALLDIR)/$(EXE)
		install $(EXE) $(INSTALLDIR);

$(EXE):      	$(OBJS)
		$(CC) $^ $(LIBS) $(OutPutOpt)$@ $(LDFLAGS) 
		@echo "$@ done"

$(OBJS)	:	$(INCLUDES) 

%.o	:	%.c
		$(CC) $(COPTS) $(INCLUDEDIR) -c -o $@ $<

