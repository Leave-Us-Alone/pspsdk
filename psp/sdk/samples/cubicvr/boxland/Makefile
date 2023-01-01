TARGET = psp_bullet
OBJS = main.o scriptingSystem.o resourceManager.o 

PSPSDK=$(shell psp-config --pspsdk-path)
INCDIR = $(PSPSDK)/../include/bullet

CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DARCH_PSP
ASFLAGS = $(CFLAGS)


LIBS = -lcubicvr -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsppower -lpsprtc -llua -lbulletdynamics -lbulletcollision -lbulletmath -lm -lstdc++ -lcubicvr 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CubicVR - Bullet Physics
PSP_EBOOT_ICON = ICON0.PNG
PSP_EBOOT_PIC1 = PIC1.PNG

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

