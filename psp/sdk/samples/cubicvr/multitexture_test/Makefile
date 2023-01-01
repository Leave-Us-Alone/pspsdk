TARGET = CubicVR_MultiTexTest
OBJS = main.o Gamepad.o

PSPSDK=$(shell psp-config --pspsdk-path)
INCDIR = $(PSPSDK)/../include/bullet

CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DARCH_PSP
ASFLAGS = $(CFLAGS)

LIBS = -lcubicvr -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsppower -lpsprtc -lbulletdynamics -lbulletcollision -lbulletmath -lm -lstdc++

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CubicVR - LWSC - Multitexture

include $(PSPSDK)/lib/build.mak

delete:
	rm -Rf $(TARGET)
	rm -Rf $(TARGET)%
	
upload:
	cp -R $(TARGET) $(PSPGAMEDIR)
	cp -R $(TARGET)% $(PSPGAMEDIR) 

uploadcontent:
	rsync -rvc --exclude=".svn" ./content/gamedata/ $(PSPGAMEDIR)$(TARGET)/

doeverything: delete clean kxploit upload uploadcontent

cubicvr:
	./make_cvr

deplus: cubicvr doeverything

