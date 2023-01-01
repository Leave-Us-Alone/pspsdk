TARGET = intraFontTest
OBJS = fonttest.o graphics.o framebuffer.o

INCDIR =
CFLAGS = -O2 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = 
LIBS = -lintraFont -lpspgum -lpspgu -lpng -lz -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = intraFont Test

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

