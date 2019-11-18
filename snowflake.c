#include "snowflake.h"


void snowflake_init(struct snowflake_s *gen, uint64_t gpid) {
    gen->gpid = gpid & 1023;
    gen->statems = 0;
}

void snowflake2_init(struct snowflake2_s *gen, uint64_t gpid) {
    gen->gpid = gpid & 0xff;
    gen->statems = 0;
}

static inline uint64_t now_ms() {
    struct timeval t;
    gettimeofday(&t, 0);
    return (uint64_t) (t.tv_sec * 1000 + t.tv_usec / 1000);
}

/////////////////////////////////////////////////////////////////////
uint64_t snowflake_nts_gen(struct snowflake_s *sf) {
    uint64_t statems = (now_ms() - SNOWFLAKE_EPOCH) << 12;

    if (sf->statems < statems) {
        sf->statems = statems-1;
    }

    sf->statems++;

    return (sf->statems<<10 | sf->gpid);
}

uint64_t snowflake2_nts_gen(struct snowflake2_s *sf) {
    uint64_t statems = (now_ms() - SNOWFLAKE_EPOCH) << 14;

    if (sf->statems < statems) {
        sf->statems = statems-1;
    }

    sf->statems++;

    return (sf->statems<<8 | sf->gpid);
}

/////////////////////////////////////////////////////////////////////////
uint64_t snowflake_gen(struct snowflake_s *sf) {
    uint64_t oldstatems = sf->statems;
    uint64_t newstatems = (now_ms() - SNOWFLAKE_EPOCH) << 12;

    if (oldstatems < newstatems) {
        __sync_bool_compare_and_swap(&sf->statems, oldstatems, newstatems-1);
    }

    uint64_t statms = __sync_add_and_fetch(&sf->statems, 1);

    return (statms<<10 | sf->gpid);
}

uint64_t snowflake2_gen(struct snowflake2_s *sf) {
    uint64_t oldstatems = sf->statems;
    uint64_t newstatems = (now_ms() - SNOWFLAKE_EPOCH) << 14;

    if (oldstatems < newstatems) {
        __sync_bool_compare_and_swap(&sf->statems, oldstatems, newstatems-1);
    }

    uint64_t statms = __sync_add_and_fetch(&sf->statems, 1);

    return (statms<<8 | sf->gpid);
}

/////////////////////////////////////////////////////////////
///id32
/////////////////////////////////////////////////////////////
void id32_init(struct id32* id, uint32_t gpid) {
    id->cnt = 0;
    id->gpid = gpid & 0xff;
}

uint32_t id32_gen(struct id32* id) {
    uint32_t cnt = __sync_add_and_fetch(&id->cnt, 1);
    return (cnt<<8) | id->gpid;
}