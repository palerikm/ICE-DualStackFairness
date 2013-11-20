
#include "../include/priority.h"


uint64_t ICELIB_pairPriority(uint32_t G, uint32_t D)
{

    uint64_t  f1 = min(G, D);
    uint64_t  f2 = max(G, D);
    uint64_t  f3 = G > D ? 1 : 0;

    return (f1 << 32) | (f2 * 2) | f3;

}



uint32_t ICELIB_calculatePriority(ICE_CANDIDATE_TYPE type, uint16_t compid, uint16_t local_pref)
{
    uint32_t typepref = 0;
    uint32_t typeprefs[] = { 0,
                             ICELIB_LOCAL_TYPEPREF,
                             ICELIB_REFLEX_TYPEREF,
                             ICELIB_RELAY_TYPEREF,
                             ICELIB_PEERREF_TYPEREF
                           };

    typepref = (0xff000000 & (typeprefs[type] << 24));

    return (typepref | local_pref<<8 | ((256 - compid) & 0xff));
}
