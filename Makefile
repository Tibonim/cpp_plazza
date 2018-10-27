NAME		= plazza

MAIN		= ./

DIRCOM		= ./communication/

DIRPARSER	= ./utils/parser/

DIRDECRYPT	= ./utils/decrypt/

DIRPROCESS	= ./project/process/

DIRCOND		= ./utils/conditionnal/

DIRMUTEX	= ./utils/mutex/

DIRCOMOBJ	= ./communication/communication/

DIRCOPYABLE	= ./utils/nonCopyable/

DIREXCEPTION	= ./project/exception/

DIRSERIALIZE	= ./communication/serialization/

DIRFORMAT	= ./utils/format/

DIRDATAFINDER	= ./utils/dataFinder/

DIRSEM		= ./utils/semaphore/

DIRKEY		= ./utils/key/

DIRKEYFINDER	= ./utils/keyFinder/

DIRHOLDER	= ./project/dataHolder/

DIRPOOL		= ./project/threadPool/

DIRREGEX	= ./utils/regex/

DIRTHREAD	= ./utils/thread/

DIRTASKQ	= ./project/taskQueue/

DIRLOG		= ./project/logHandler/

INCTHREAD	= ./utils/thread/include_files/

DIRINTSOCKET	= ./communication/intSocket/

DIRUNIXSOCKET	= ./communication/unixSocket/

DIRFIFOPIPES	= ./communication/fifoPipes/

DIRFACTORY	= ./project/factory/

DIRBARRIER	= ./utils/barrier/

DIRLAUNCHER	= ./project/launcher/

INCLAUNCHER	= $(DIRLAUNCHER)include_files/

INCCOMOBJ	= $(DIRCOMOBJ)include_files/

INCHOLDER	= $(DIRHOLDER)include_files/

INCDECRYPT	= $(DIRDECRYPT)include_files/

INCPOOL		= $(DIRPOOL)include_files/

INCTASKQ	= $(DIRTASKQ)include_files/

INCCOPYABLE	= $(DIRCOPYABLE)include_files/

INCFACTORY	= $(DIRFACTORY)include_files/

INCFORMAT	= $(DIRFORMAT)include_files/

INCDATAFINDER	= $(DIRDATAFINDER)include_files/

INCKEYFINDER	= $(DIRKEYFINDER)include_files/

INCPROCESS	= $(DIRPROCESS)include_files/

INCEXCEPTION	= $(DIREXCEPTION)include_files/

INCPARSER	= $(DIRPARSER)include_files/

INCCOND		= $(DIRCOND)include_files/

INCMUTEX	= $(DIRMUTEX)include_files/

INCREGEX	= $(DIRREGEX)include_files/

INCFACTORY	= $(DIRFACTORY)include_files/

INCSERIALIZE	= $(DIRSERIALIZE)include_files/

INCBARRIER	= $(DIRBARRIER)include_files/

INCSEM		= $(DIRSEM)include_files/

INCKEY		= $(DIRKEY)include_files/

INCLOG		= $(DIRLOG)include_files/

INCCOM		= ./communication/include_files/

INCINTSOCKET	= ./communication/intSocket/include_files/

INCUNIXSOCKET	= ./communication/unixSocket/include_files/

INCFIFOPIPES	= ./communication/fifoPipes/include_files/

SRC		= $(DIRDATAFINDER)DataFinder.cpp \
		  $(DIRKEYFINDER)KeyFinder.cpp \
	          $(DIRCOM)ACom.cpp \
		  $(DIRFIFOPIPES)fifoPipes.cpp \
		  $(DIRFORMAT)Format.cpp \
		  $(DIRREGEX)Regex.cpp \
		  $(DIRDECRYPT)Cesar.cpp \
		  $(DIRDECRYPT)Xor.cpp \
		  $(DIRINTSOCKET)intSocket.cpp \
		  $(DIRUNIXSOCKET)unixSocket.cpp \
		  $(DIRPARSER)ParseInput.cpp \
		  $(DIRPARSER)treeInfo.cpp \
		  $(DIRPARSER)ParseTree.cpp \
		  $(DIRPROCESS)AProcess.cpp \
		  $(DIRPROCESS)FatherProcess.cpp \
		  $(DIRTHREAD)thread.cpp \
		  $(DIRCOND)conditionnal.cpp \
		  $(DIRCOND)timeElaps.cpp \
		  $(DIREXCEPTION)CustomException.cpp \
		  $(DIREXCEPTION)DataFinderException.cpp \
		  $(DIREXCEPTION)KeyFinderException.cpp \
		  $(DIREXCEPTION)CondException.cpp \
		  $(DIREXCEPTION)FormatException.cpp \
		  $(DIREXCEPTION)RegexException.cpp \
		  $(DIREXCEPTION)FactoryException.cpp \
		  $(DIREXCEPTION)treeInfoException.cpp \
		  $(DIREXCEPTION)ComException.cpp \
		  $(DIREXCEPTION)dataHolderException.cpp \
		  $(DIREXCEPTION)timeException.cpp \
		  $(DIREXCEPTION)PipesException.cpp \
		  $(DIREXCEPTION)SockException.cpp \
		  $(DIRMUTEX)mutex.cpp \
		  $(DIRMUTEX)scopeLock.cpp \
		  $(DIRHOLDER)dataHolder.cpp \
		  $(DIRPOOL)threadPool.cpp \
		  $(DIRPROCESS)ChildProcess.cpp \
		  $(DIRCOMOBJ)communication.cpp \
		  $(DIRFACTORY)comFactory.cpp \
		  $(DIRCOMOBJ)InterCom.cpp \
		  $(DIRSERIALIZE)serialization.cpp \
		  $(DIREXCEPTION)ForkException.cpp \
		  $(DIRPROCESS)Fork.cpp \
		  $(DIRBARRIER)barrier.cpp \
		  $(DIRLAUNCHER)launcher.cpp \
		  $(DIREXCEPTION)barrierException.cpp \
		  $(DIRLOG)logHandler.cpp \
		  $(MAIN)main.cpp

LDFLAGS		= -lpthread

CPPFLAGS	= -Wall -Werror -Wextra -std=c++11 \
		  -I$(INCCOM) -I$(INCPARSER) -I$(INCPROCESS) \
		  -I$(INCEXCEPTION) -I$(INCINTSOCKET) -I$(INCUNIXSOCKET) \
		  -I$(INCTHREAD) -I$(INCCOND) -I$(INCEXCEPTION) \
		  -I$(INCMUTEX) -I$(INCFORMAT) -I$(INCREGEX) \
		  -I$(INCCOPYABLE) -I$(INCHOLDER) -I$(INCTASKQ) \
		  -I$(INCPOOL) -I$(INCFACTORY) -I$(INCCOMOBJ) \
		  -I$(INCFACTORY) -I$(INCSERIALIZE) \
		  -I$(INCDATAFINDER) -I$(INCDECRYPT) -I$(INCBARRIER) \
		  -I$(INCFIFOPIPES) -I$(INCKEYFINDER) -I$(INCLAUNCHER) \
		  -I$(INCLOG)

OBJ		= $(SRC:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
	g++ $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all
