TARGET = CubicVR_Courtyard
OBJS = main.o Gamepad.o

PSPSDK=$(shell psp-config --pspsdk-path)
INCDIR = $(PSPSDK)/../include/bullet

CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DARCH_PSP
ASFLAGS = $(CFLAGS)


LIBS = -lcubicvr -lbulletdynamics -lbulletcollision -lbulletmath -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsppower -lpsprtc -lm -lstdc++

LDFLAGS  := $(addprefix -L,$(LIBDIR)) $(LDFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CubicVR - LWSC - Courtyard

include $(PSPSDK)/lib/build.mak

delete:
	rm -Rf $(TARGET)
	rm -Rf $(TARGET)%
	
upload:
	cp -R $(TARGET) $(PSPGAMEDIR)
	cp -R $(TARGET)% $(PSPGAMEDIR) 

uploadcontent:
	rsync -rvc --exclude=".svn" ./content/gamedata/ $(PSPGAMEDIR)$(TARGET)/
#	cp -R ./content/gamedata/* $(PSPGAMEDIR)$(TARGET)

debugfolder:
	rm -rf debug/* debug/.svn
	cp -R *.elf debug/ 
	cp -R ./content/gamedata/ debug/
	
doeverything: delete clean kxploit upload uploadcontent

cubicvr:
	./make_cvr

deplus: cubicvr doeverything

