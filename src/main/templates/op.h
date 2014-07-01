#ifndef {op}_H
#define {op}_H

{apisubst}
#ifdef __cplusplus
extern "C" {{
#endif
{prototypes}
#ifdef __cplusplus
}}
#endif

#define {op}_IMPLEMENTATION "{o}/{p}/{impldir}"
#ifndef {op}_VERSION
#define {op}_VERSION "-"
#endif

#endif
