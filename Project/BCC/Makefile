SRC = ..\test\*.cpp ..\*.cpp 
INCLUDES = ..\test\*.h ..\*.h 
LIBS = ..\*.lib 
INCLUDEPATH = C:\bc31\include;..\test;..\;
LIBSPATH = C:\bc31\lib;..\;
TARGET = Project.exe
$(TARGET):	$(SRC) $(INCLUDES) configuration.xmi
	bcc.exe -mh -v -e$(TARGET) -I$(INCLUDEPATH) -L$(LIBSPATH) $(SRC) $(LIBS)
all:	$(TARGET)
clean:
	-del *.obj
	-del $(TARGET)
	-del *.asm
configuration.xmi:	
	configuration.xmi