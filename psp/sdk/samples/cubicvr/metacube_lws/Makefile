TARGET = CubicVR_MetaCube
OBJS = main.o Gamepad.o

PSPSDK=$(shell psp-config --pspsdk-path)
INCDIR = $(PSPSDK)/../include/bullet

CFLAGS = -Wall -O3
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DARCH_PSP
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PSP_FW_VERSION = 390
PSP_LARGE_MEMORY = 1

LIBS = -lcubicvr -lbulletdynamics -lbulletcollision -lbulletmath -lpspgum -lpspgu -lstdc++ -lm -lpsprtc

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CubicVR Metacube


release: delete all
	@mkdir $(TARGET) || true
	cp EBOOT.PBP $(TARGET)
	cp ./content/gamedata/* $(TARGET) || true


debug:	all debugfolder
		

include $(PSPSDK)/lib/build.mak

delete:
	rm -rf $(TARGET)
	
upload:
	cp -R $(TARGET) $(PSPGAMEDIR)

debugfolder:
	@mkdir debug || true
	rm -rf debug/* debug/.svn
	cp -R *.elf debug/ 
	cp -R ./content/gamedata/ debug/



