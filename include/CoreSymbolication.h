/**
 * Name: libsymbolicate
 * Type: iOS/OS X shared library
 * Desc: Library for symbolicating memory addresses.
 *
 * Author: Lance Fetters (aka. ashikase)
 * License: LGPL v3 (See LICENSE file for details)
 */

// NOTE: The information in this file is based off of:
//       https://github.com/mountainstorm/CoreSymbolication.git

#ifndef SYMBOLICATE_CORESYMBOLICATION_H_
#define SYMBOLICATE_CORESYMBOLICATION_H_

typedef struct _CSTypeRef {
    void *csCppData;
    void *csCppObj;
} CSTypeRef;

//typedef CSTypeRef CSRegionRef;
//typedef CSTypeRef CSSourceInfoRef;
typedef CSTypeRef CSSymbolicatorRef;
typedef CSTypeRef CSSymbolOwnerRef;
//typedef CSTypeRef CSSectionRef;
//typedef CSTypeRef CSSegmentRef;
typedef CSTypeRef CSSymbolRef;

typedef struct _CSRange {
   unsigned long long location;
   unsigned long long length;
} CSRange;

//typedef int (^CSRegionIterator)(CSRegionRef region);
//typedef int (^CSSegmentIterator)(CSSegmentRef segment);
typedef int (^CSSymbolIterator)(CSSymbolRef symbol);

typedef struct _CSArchitecture {
    cpu_type_t cpu_type;
    cpu_subtype_t cpu_subtype;
} CSArchitecture;

#define kCSNow  0x80000000u

extern "C" {
    // Allocation-related functions.
    Boolean CSIsNull(CSTypeRef cs);
    CSTypeRef CSRetain(CSTypeRef cs);
    void CSRelease(CSTypeRef cs);

    // CSArchitecture
    CSArchitecture CSArchitectureGetArchitectureForName(const char *arch);

    // CSSymbolicator
    CSSymbolicatorRef CSSymbolicatorCreateWithPathAndArchitecture(const char *path, CSArchitecture arch);
    CSSymbolOwnerRef CSSymbolicatorGetSymbolOwnerWithCFUUIDBytesAtTime(CSSymbolicatorRef symbolicator, CFUUIDBytes *uuid, uint64_t time);

    // CSSymbolOwner
    long CSSymbolOwnerForeachSymbol(CSSymbolOwnerRef owner, CSSymbolIterator block);
    CSSymbolRef CSSymbolOwnerGetSymbolWithAddress(CSSymbolOwnerRef owner, uint64_t addr);

    // CSSymbol
    const char * CSSymbolGetName(CSSymbolRef sym);
    CSRange CSSymbolGetRange(CSSymbolRef sym);
    Boolean CSSymbolIsObjcMethod(CSSymbolRef sym);
    Boolean CSSymbolIsFunction(CSSymbolRef sym);

    // Currently unused.
#if 0
    CSRegionRef CSSymbolOwnerGetRegionWithName(CSSymbolOwnerRef owner, const char *name);
    const char * CSRegionGetName(CSRegionRef region);
    CSRange CSRegionGetRange(CSRegionRef region);

    int64_t CSSymbolOwnerGetBaseAddress(CSSymbolOwnerRef owner);
    unsigned int CSSymbolOwnerIsDyldSharedCache(CSSymbolOwnerRef owner);

    int CSSymbolOwnerForeachSegment(CSSymbolOwnerRef owner, CSSegmentIterator block);
    int CSSymbolOwnerForeachRegionWithName(CSSymbolOwnerRef owner, const char *name, CSRegionIterator block);
#endif
}

#endif // SYMBOLICATE_CORESYMBOLICATION_H_

/* vim: set ft=objcpp ff=unix sw=4 ts=4 tw=80 expandtab: */