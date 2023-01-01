TARGET = lua_basic
OBJS = main.o scriptingSystem.o resourceManager.o

PSPSDK=$(shell psp-config --pspsdk-path)
INCDIR = $(PSPSDK)/../include/bullet

CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DARCH_PSP
ASFLAGS = $(CFLAGS)

LIBS = -lcubicvr -lbulletdynamics -lbulletcollision -lbulletmath -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsppower -lpsprtc -llua -lm -lstdc++

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CubicVR - Lua Gamepad
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
	cp -R ./content/gamedata/* $(PSPGAMEDIR)$(TARGET)
	
doeverything: delete clean kxploit upload uploadcontent

