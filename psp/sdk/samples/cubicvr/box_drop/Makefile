TARGET = psp_bullet
OBJS = main.o scriptingSystem.o resourceManager.o 

PSPSDK=$(shell psp-config --pspsdk-path)
INCDIR = $(PSPSDK)/../include/bullet


#CFLAGS = -G0 -Wall
#CFLAGS = -g
CFLAGS = -O2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DARCH_PSP
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PSP_FW_VERSION = 390
PSP_LARGE_MEMORY = 1

LIBS = -lcubicvr -lbulletsoftbody -lbulletdynamics -lbulletcollision -lbulletmath -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsppower -lpsprtc -llua -lm -lstdc++ -lcubicvr

LDFLAGS  := $(addprefix -L,$(LIBDIR)) $(LDFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CubicVR - Bullet Physics
PSP_EBOOT_ICON = ICON0.PNG
PSP_EBOOT_PIC1 = PIC1.PNG


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
	cp -R ./content/gamedata/* $(PSPGAMEDIR)$(TARGET)

debugfolder:
	@mkdir debug || true
	rm -rf debug/* debug/.svn
	cp -R *.elf debug/ 
	cp -R ./content/gamedata/ debug/
