TARGET = CVRDEMOS
OBJS = main.o scriptingSystem.o resourceManager.o

PSPSDK=$(shell psp-config --pspsdk-path)
INCDIR = $(PSPSDK)/../include/bullet

CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DARCH_PSP
ASFLAGS = $(CFLAGS)


LIBS = -lcubicvr -lbulletdynamics -lbulletcollision -lbulletmath -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsppower -lpsprtc -llua -lm -lstdc++

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CubicVR - Demo Launcher
PSP_EBOOT_ICON = ICON0.PNG
PSP_EBOOT_PIC1 = PIC1.PNG

include $(PSPSDK)/lib/build.mak

delete:
	rm -Rf $(TARGET)
	rm -Rf $(TARGET)%
	
upload:
	rsync -rvc --exclude=".svn" $(TARGET) $(PSPGAMEDIR)
	rsync -rvc --exclude=".svn" $(TARGET)% $(PSPGAMEDIR)

downloadpsp:
	rsync -rvc --exclude="EBOOT.PBP" $(PSPGAMEDIR)$(TARGET)/ ./content/gamedata/
	
uploadcontent:
	rsync -rvc --exclude=".svn" ./content/gamedata/ $(PSPGAMEDIR)$(TARGET)/
	
purge:
	rm -Rf $(TARGET)
	rm -Rf $(TARGET)%
	rm -Rf $(PSPGAMEDIR)$(TARGET)
	rm -Rf $(PSPGAMEDIR)$(TARGET)%
		
doeveverything: delete clean kxploit upload uploadcontent

psp: delete kxploit upload uploadcontent
