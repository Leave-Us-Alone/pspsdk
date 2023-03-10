/**
 * Identify the characteristics of the host CPU.
 *
 * Implemented according to:

- AP-485 Intel(C) Processor Identification and the CPUID Instruction
	$(LINK http://www.intel.com/design/xeon/applnots/241618.htm)

- Intel(R) 64 and IA-32 Architectures Software Developer's Manual, Volume 2A: Instruction Set Reference, A-M
	$(LINK http://developer.intel.com/design/pentium4/manuals/index_new.htm)

- AMD CPUID Specification Publication # 25481
	$(LINK http://www.amd.com/us-en/assets/content_type/white_papers_and_tech_docs/25481.pdf)

Example:
---
import std.cpuid;
import std.stdio;

void main()
{
    writefln(std.cpuid.toString());
}
---

AUTHORS:	Tomas Lindquist Olsen &lt;tomas@famolsen.dk&gt;
		(slightly altered by Walter Bright)
COPYRIGHT:	Public Domain

 * BUGS:	Only works on x86 CPUs
 *
 * Macros:
 *	WIKI = Phobos/StdCpuid
 *	COPYRIGHT = Public Domain
 */

/* NOTE: This file has been patched from the original DMD distribution to
   work with the GDC compiler.

   Modified by David Friedman, November 2006
*/

module std.cpuid;

import std.string;

version(D_InlineAsm_X86)
{
    /// Returns everything as a printable string
    char[] toString()
    {
	char[] feats;
	if (mmx)			feats ~= "MMX ";
	if (fxsr)			feats ~= "FXSR ";
	if (sse)			feats ~= "SSE ";
	if (sse2)			feats ~= "SSE2 ";
	if (sse3)			feats ~= "SSE3 ";
	if (ssse3)			feats ~= "SSSE3 ";
	if (amd3dnow)			feats ~= "3DNow! ";
	if (amd3dnowExt)		feats ~= "3DNow!+ ";
	if (amdMmx)			feats ~= "MMX+ ";
	if (ia64)			feats ~= "IA-64 ";
	if (amd64)			feats ~= "AMD64 ";
	if (hyperThreading)		feats ~= "HTT";

	return format(
		"Vendor string:    %s\n", vendor,
		"Processor string: %s\n", processor,
		"Signature:        Family=%d Model=%d Stepping=%d\n", family, model, stepping,
		"Features:         %s\n", feats,
		"Multithreading:   %d threads / %d cores\n", threadsPerCPU, coresPerCPU);

    }

    /// Returns vendor string
    char[] vendor()		{return vendorStr;}
    /// Returns processor string
    char[] processor()		{return processorStr;}

    /// Is MMX supported?
    bool mmx()			{return (flags&MMX_BIT)!=0;}
    /// Is FXSR supported?
    bool fxsr()			{return (flags&FXSR_BIT)!=0;}
    /// Is SSE supported?
    bool sse()			{return (flags&SSE_BIT)!=0;}
    /// Is SSE2 supported?
    bool sse2()			{return (flags&SSE2_BIT)!=0;}
    /// Is SSE3 supported?
    bool sse3()			{return (misc&SSE3_BIT)!=0;}
    /// Is SSSE3 supported?
    bool ssse3()		{return (misc&SSSE3_BIT)!=0;}

    /// Is AMD 3DNOW supported?
    bool amd3dnow()		{return (exflags&AMD_3DNOW_BIT)!=0;}
    /// Is AMD 3DNOW Ext supported?
    bool amd3dnowExt()		{return (exflags&AMD_3DNOW_EXT_BIT)!=0;}
    /// Is AMD MMX supported?
    bool amdMmx()		{return (exflags&AMD_MMX_BIT)!=0;}

    /// Is this an Intel Architecture IA64?
    bool ia64()			{return (flags&IA64_BIT)!=0;}
    /// Is this an AMD 64?
    bool amd64()		{return (exflags&AMD64_BIT)!=0;}

    /// Is hyperthreading supported?
    bool hyperThreading()	{return (flags&HTT_BIT)!=0;}
    /// Returns number of threads per CPU
    uint threadsPerCPU()	{return maxThreads;}
    /// Returns number of cores in CPU
    uint coresPerCPU()		{return maxCores;}

    /// Is this an Intel processor?
    bool intel()		{return manufac==INTEL;}
    /// Is this an AMD processor?
    bool amd()			{return manufac==AMD;}

    /// Returns stepping
    uint stepping()		{return _stepping;}
    /// Returns model
    uint model()		{return _model;}
    /// Returns family
    uint family()		{return _family;}
    //uint processorType()	{return (signature>>>12)&0x3;}

    static this()
    {
	getVendorString(vendorStr.ptr);
	processorStr = getProcessorString();
	getFeatureFlags(& flags, & misc, & exflags, & apic, & signature);

	// stepping / family / model
	_stepping = signature&0xF;
	uint fbase = (signature>>>8)&0xF;
	uint fex = (signature>>>20)&0xFF;
	uint mbase = (signature>>>4)&0xF;
	uint mex = (signature>>>16)&0xF;

	// vendor specific
	void function() threadFn;
	switch(vendorStr)
	{
	    case "GenuineIntel":
		    manufac = INTEL;
		    threadFn = &getThreadingIntel;
		    if (fbase == 0xF)
			    _family = fbase+fex;
		    else
			    _family = fbase;
		    if (_family == 0x6 || _family == 0xF)
			    _model = mbase+(mex<<4);
		    else
			    _model = mbase;
		    break;

	    case "AuthenticAMD":
		    manufac = AMD;
		    threadFn = &getThreadingAMD;
		    if (fbase < 0xF)
		    {
			    _family = fbase;
			    _model = mbase;
		    }
		    else
		    {
			    _family = fbase+fex;
			    _model = mbase+(mex<<4);
		    }
		    break;

	    default:
		    manufac = OTHER;
	}

	// threading details
	if (hyperThreading && threadFn !is null)
	{
		threadFn();
	}
    }

private:
    // feature flags
    enum : uint
    {
	    MMX_BIT = 1<<23,
	    FXSR_BIT = 1<<24,
	    SSE_BIT = 1<<25,
	    SSE2_BIT = 1<<26,
	    HTT_BIT = 1<<28,
	    IA64_BIT = 1<<30
    }
    // feature flags misc
    enum : uint
    {
	    SSE3_BIT = 1,
	    SSSE3_BIT = 1<<9
    }
    // extended feature flags
    enum : uint
    {
	    AMD_MMX_BIT = 1<<22,
	    AMD64_BIT = 1<<29,
	    AMD_3DNOW_EXT_BIT = 1<<30,
	    AMD_3DNOW_BIT = 1<<31
    }
    // manufacturer
    enum
    {
	    OTHER,
	    INTEL,
	    AMD
    }

    uint flags, misc, exflags, apic, signature;
    uint _stepping, _model, _family;

    char[12] vendorStr = "";
    char[] processorStr = "";

    uint maxThreads=1;
    uint maxCores=1;
    uint manufac=OTHER;

    /* **
     * fetches the cpu vendor string
     */
    private void getVendorString(char* dst)
    {
	// puts the vendor string into dst
	asm
	{
	    push EBX                    ;
	    mov EAX, 0			;
	    cpuid			;
	    mov EAX, dst		;
	    mov [EAX], EBX		;
	    mov [EAX+4], EDX		;
	    mov [EAX+8], ECX		;
	    db 0x5b  /* pop EBX */      ;
	}
    }

    private char[] getProcessorString()
    {
	char[48] buffer;
	char* dst = buffer.ptr;
	// puts the processor string into dst
	asm
	{
	    push EBX                    ;
	    mov EAX, 0x8000_0000	;
	    cpuid			;
	    cmp EAX, 0x8000_0004	;
	    jb PSLabel			; // no support
	    push EDI			;
	    mov EDI, dst		;
	    mov EAX, 0x8000_0002	;
	    cpuid			;
	    mov [EDI], EAX		;
	    mov [EDI+4], EBX		;
	    mov [EDI+8], ECX		;
	    mov [EDI+12], EDX		;
	    mov EAX, 0x8000_0003	;
	    cpuid			;
	    mov [EDI+16], EAX		;
	    mov [EDI+20], EBX		;
	    mov [EDI+24], ECX		;
	    mov [EDI+28], EDX		;
	    mov EAX, 0x8000_0004	;
	    cpuid			;
	    mov [EDI+32], EAX		;
	    mov [EDI+36], EBX		;
	    mov [EDI+40], ECX		;
	    mov [EDI+44], EDX		;
	    pop EDI			;
	PSLabel:			;
	    db 0x5b  /* pop EBX */      ;
	}

	if (buffer[0] == char.init) // no support
	    return "";

	// seems many intel processors prepend whitespace
	return std.string.strip(std.string.toString(dst)).dup;
    }

    private void getFeatureFlags(uint *flags, uint *misc, uint *exflags,
	uint *apic, uint *signature)
    {
	uint f,m,e,a,s;
	asm
	{
	    push EBX                    ;
	    mov EAX, 0			;
	    cpuid			;
	    cmp EAX, 1			;
	    jb FeatLabel		; // no support
	    mov EAX, 1			;
	    cpuid			;
	    mov f, EDX			;
	    mov m, ECX			;
	    mov a, EBX			;
	    mov s, EAX			;

	FeatLabel:			;
	    mov EAX, 0x8000_0000	;
	    cpuid			;
	    cmp EAX, 0x8000_0001	;
	    jb FeatLabel2		; // no support
	    mov EAX, 0x8000_0001	;
	    cpuid			;
	    mov e, EDX			;

	FeatLabel2:
	    db 0x5b  /* pop EBX */      ;
	    ;
	}
	*flags = f;
	*misc = m;
	*exflags = e;
	*apic = a;
	*signature = s;
    }

    private void getThreadingIntel()
    {
	uint n;
	ubyte b = 0;
	asm
	{
	    push EBX                    ;
	    mov EAX, 0			;
	    cpuid			;
	    cmp EAX, 4			;
	    jb IntelSingle		;
	    mov EAX, 4			;
	    mov ECX, 0			;
	    cpuid			;
	    mov n, EAX			;
	    mov b, 1			;
	IntelSingle:			;
	    db 0x5b  /* pop EBX */      ;
	}
	if (b != 0)
	{
	    maxCores = ((n>>>26)&0x3F)+1;
	    maxThreads = (apic>>>16)&0xFF;
	}
	else
	{
	    maxCores = maxThreads = 1;
	}
    }

    private void getThreadingAMD()
    {
	ubyte n;
	ubyte b = 0;
	asm
	{
	    push EBX                    ;
	    mov EAX, 0x8000_0000	;
	    cpuid			;
	    cmp EAX, 0x8000_0008	;
	    jb AMDSingle		;
	    mov EAX, 0x8000_0008	;
	    cpuid			;
	    mov n, CL			;
	    mov b, 1			;
	AMDSingle:			;
	    db 0x5b  /* pop EBX */      ;
	}
	if (b != 0)
	{
	    maxCores = n+1;
	    maxThreads = (apic>>>16)&0xFF;
	}
	else
	{
	    maxCores = maxThreads = 1;
	}
    }
}
else
{
    char[] toString() { return "unknown CPU\n"; }

    char[] vendor()		{return "unknown vendor"; }
    char[] processor()		{return "unknown processor"; }

    bool mmx()			{return false; }
    bool fxsr()			{return false; }
    bool sse()			{return false; }
    bool sse2()			{return false; }
    bool sse3()			{return false; }
    bool ssse3()		{return false; }

    bool amd3dnow()		{return false; }
    bool amd3dnowExt()		{return false; }
    bool amdMmx()		{return false; }

    bool ia64()			{return false; }
    bool amd64()		{return false; }

    bool hyperThreading()	{return false; }
    uint threadsPerCPU()	{return 0; }
    uint coresPerCPU()		{return 0; }

    bool intel()		{return false; }
    bool amd()			{return false; }

    uint stepping()		{return 0; }
    uint model()		{return 0; }
    uint family()		{return 0; }
}
