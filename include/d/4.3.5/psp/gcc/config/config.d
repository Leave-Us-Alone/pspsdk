module gcc.config.config;

const bool Have_strtold = 0;

// C stdio config for std.stdio
const bool Have_fwide = 0;
const bool Have_getdelim = 0;
const bool Have_fgetln = 0;
const bool Have_fgetline = 0;
const bool Have_Unlocked_Stdio = 0;
const bool Have_Unlocked_Wide_Stdio = 0;

// fpclassify / signbit interface
const bool Use_IEEE_fpsb = 0;

// Some kind of memory map interface that std.mmfile can use
// const bool Have_Memory_Map = @DCFG_HAVE_MEMORY_MAP@;
version (Windows)
    const bool Have_Memory_Map = true;
else version (Unix)
    const bool Have_Memory_Map = true;
else
    const bool Have_Memory_Map = true;

const bool Use_ARM_EABI_Unwinder = 0;
