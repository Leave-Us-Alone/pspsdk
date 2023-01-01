TARGET = cvr_font
OBJS = font.c main.o
#TO-DO: OBJS = main.o scriptingSystem.o resourceManager.o
	
PSPSDK=$(shell psp-config --pspsdk-path)
INCDIR = $(PSPSDK)/../include/bullet
CFLAGS = -G0 -Wall -O2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti  -DARCH_PSP
ASFLAGS = $(CFLAGS)

LDFLAGS  := $(addprefix -L,$(LIBDIR)) $(LDFLAGS)
LIBS= -lcubicvr -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsppower -lpsprtc -llua -lm -lstdc++

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CubicVR - Font
PSP_EBOOT_ICON = ICON0.PNG
PSP_EBOOT_PIC1 = PIC1.PNG

CVR_OMIT_FOLDERS = -rvc --exclude=".svn"

include $(PSPSDK)/lib/build.mak

delete:
	rm -Rf __SCE__$(TARGET)
	rm -Rf %__SCE__$(TARGET)

upload:
	bin2c font.raw font.c font
	rsync $(CVR_OMIT_FOLDERS) %__SCE__$(TARGET) $(PSPGAMEDIR)
	rsync $(CVR_OMIT_FOLDERS) %__SCE__$(TARGET) $(PSPGAMEDIR)

uploadcontent:
	rsync $(CVR_OMIT_FOLDERS) ./content/gamedata/ $(PSPGAMEDIR)__SCE__$(TARGET)/

doeverything: delete clean SCEkxploit upload uploadcontent

# CVR PSP START
psppurge: pspclean
	rm -Rf $(PSPGAMEDIR)__SCE__$(TARGET)/
	rm -Rf $(PSPGAMEDIR)%__SCE__$(TARGET)/

psplink: upload uploadcontent
	cp $(TARGET).elf $(PSPGAMEDIR)__SCE__$(TARGET)/
	
pspclean: delete clean
pspsync: upload uploadcontent
pspall: pspclean psp pspsync
psp: SCEkxploit

# CVR PSP END

# /////////////////////////////////////////////////

cubicvr:
	./make_cvr

deplus: cubicvr doeverything

font.c : font.raw
	bin2c font.raw font.c font
	
