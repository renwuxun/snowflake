#include "snowflake.h"


int snowflake_generator_init(struct snowflake_generator_s* gen, uint64_t gpid) {
    if (gpid > 1023) {
        return __LINE__;
    }

    gen->gpid = gpid;
    gen->statems = 0;

    return 0;
}

int snowflake_generator2_init(struct snowflake_generator2_s* gen, uint64_t gpid) {
    if (gpid > 255) {
        return __LINE__;
    }

    gen->gpid = gpid;
    gen->statems = 0;

    return 0;
}

static uint64_t now_ms() {
    struct timeval t;
    gettimeofday(&t, 0);
    return (uint64_t)(t.tv_sec*1000 + t.tv_usec/1000);
}

uint64_t snowflake_generator_gen(struct snowflake_generator_s* gen) {
    uint64_t nowms = now_ms() - SNOWFLAKE_EPOCH;

    if ((gen->statems >> 22) == nowms) {
        gen->statems++;
        //gen->statems = gen->statems &~ 0x3ff000; // 清理gpid的位置
    } else {
        gen->statems = nowms<<22;
    }

    return gen->statems | gen->gpid<<12;
}

uint64_t snowflake_generator2_gen(struct snowflake_generator2_s* gen) {
    uint64_t nowms = now_ms() - SNOWFLAKE_EPOCH;

    if ((gen->statems >> 22) == nowms) {
        gen->statems++;
        //gen->statems = gen->statems &~ 0x3fc000; // 清理gpid的位置
    } else {
        gen->statems = nowms<<22;
    }

    return gen->statems | gen->gpid<<14;
}

