#include "snowflake.h"


int snowflake_init(struct snowflake_s *gen, uint64_t gpid) {
    if (gpid > 1023) {
        return __LINE__;
    }

    gen->gpid = gpid;
    gen->statems = 0;

    return 0;
}

int snowflake2_init(struct snowflake2_s *gen, uint64_t gpid) {
    if (gpid > 255) {
        return __LINE__;
    }

    gen->gpid = gpid;
    gen->statems = 0;

    return 0;
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
