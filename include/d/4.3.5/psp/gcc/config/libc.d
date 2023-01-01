module gcc.config.libc;
private import gcc.builtins;

alias __builtin_Clong Clong_t;
alias __builtin_Culong Culong_t;
alias int off_t;
alias dchar wchar_t;
alias int time_t;
alias uint clock_t;
const uint CLOCKS_PER_SEC = 1000000;
struct tm
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
}

const int RAND_MAX = 2147483647;
const int EOF = -1;
const int FILENAME_MAX = 1024;
const int TMP_MAX = 26;
const int FOPEN_MAX = 20;
const int L_tmpnam = 1024;
const size_t FILE_struct_size = 104;
alias int fpos_t;
