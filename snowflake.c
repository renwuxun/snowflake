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

uint64_t snowflake_nts_gen(struct snowflake_s *gen) {
    uint64_t nowms = now_ms() - SNOWFLAKE_EPOCH;

    if ((gen->statems >> 12) < nowms) {
        gen->statems = nowms << 12;
    }

    gen->statems++;
    //gen->statems = gen->statems &~ 0x3fc000; // 清理gpid的位置

    return gen->statems | gen->gpid << 56;
}

uint64_t snowflake2_nts_gen(struct snowflake2_s *gen) {
    uint64_t nowms = now_ms() - SNOWFLAKE_EPOCH;

    if ((gen->statems >> 14) < nowms) {
        gen->statems = nowms << 14;
    }

    gen->statems++;
    //gen->statems = gen->statems &~ 0x3fc000; // 清理gpid的位置

    return gen->statems | gen->gpid << 56;
}

uint64_t snowflake_gen(struct snowflake_s *gen) {
    uint64_t nowms = now_ms() - SNOWFLAKE_EPOCH;

    if ((gen->statems >> 12) < nowms) {
        gen->statems = nowms << 12;
    }

    __sync_fetch_and_add(&gen->statems, 1);
    //gen->statems = gen->statems &~ 0x3fc000; // 清理gpid的位置

    return gen->statems | gen->gpid << 56;
}

uint64_t snowflake2_gen(struct snowflake2_s *gen) {
    uint64_t nowms = now_ms() - SNOWFLAKE_EPOCH;

    if ((gen->statems >> 14) < nowms) {
        gen->statems = nowms << 14;
    }

    __sync_fetch_and_add(&gen->statems, 1);
    //gen->statems = gen->statems &~ 0x3fc000; // 清理gpid的位置

    return gen->statems | gen->gpid << 56;
}
