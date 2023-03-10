module gcc.config.mathfuncs;

private import gcc.config.libc;
private import gcc.builtins;

// We don't have long double functions..

extern (C) { // prob doesn't matter..
alias __builtin_acos acosl;
alias __builtin_asin asinl;
alias __builtin_atan atanl;
alias __builtin_atan2 atan2l;
alias __builtin_cos cosl;
alias __builtin_sin sinl;
alias __builtin_tan tanl;
alias __builtin_acosh acoshl;
alias __builtin_asinh asinhl;
alias __builtin_atanh atanhl;
alias __builtin_cosh coshl;
alias __builtin_sinh sinhl;
alias __builtin_tanh tanhl;
alias __builtin_exp expl;
alias __builtin_exp2 exp2l;
alias __builtin_expm1 expm1l;

alias __builtin_frexp frexpl;

alias __builtin_ilogb ilogbl;
alias __builtin_ldexp ldexpl;
alias __builtin_log logl;
alias __builtin_log10 log10l;
alias __builtin_log1p log1pl;
alias __builtin_log2 log2l;
alias __builtin_logb logbl;

//alias gcc.config.modfl __builtin_modf;
extern (D) real modfl(real x, real * py) {
    double dx = x;
    double y;
    double result = __builtin_modf(dx, & y);
    *py = y;
    return result;
}

alias __builtin_scalbn scalbnl;
alias __builtin_scalbln scalblnl;
alias __builtin_cbrt cbrtl;
alias __builtin_fabs fabsl;
alias __builtin_hypot hypotl;
alias __builtin_pow powl;
alias __builtin_sqrt sqrtl;
alias __builtin_erf erfl;
alias __builtin_erfc erfcl;
alias __builtin_lgamma lgammal;
alias __builtin_tgamma tgammal;
alias __builtin_ceil ceill;
alias __builtin_floor floorl;
alias __builtin_nearbyint nearbyintl;
alias __builtin_rint rintl;
alias __builtin_lrint lrintl;
alias __builtin_llrint llrintl;
alias __builtin_round roundl;
alias __builtin_lround lroundl;
alias __builtin_llround llroundl;
alias __builtin_trunc truncl;
alias __builtin_fmod fmodl;
alias __builtin_remainder remainderl;
alias __builtin_remquo remquol;
alias __builtin_copysign copysignl;
//alias __builtin_nan nanl;
real nan(char *);
alias nan nanl;
alias __builtin_nextafter nextafterl;
alias __builtin_nextafter nexttowardl;
alias __builtin_fdim fdiml;
alias __builtin_fmax fmaxl;
alias __builtin_fmin fminl;
alias __builtin_fmal fmal;

alias __builtin_sqrt sqrt;
//alias __builtin_sqrtf sqrtf;//noldfuncs
}

alias __builtin_sqrtf sqrtf;
