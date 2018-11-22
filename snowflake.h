#ifndef SNOWFLAKE_GENERATOR_H
#define SNOWFLAKE_GENERATOR_H


#include <stdint.h>
#include <sys/time.h>


#define SNOWFLAKE_EPOCH 1538006400000


struct snowflake_generator_s {
    uint64_t statems;
    uint64_t gpid;
};

struct snowflake_generator2_s {
    uint64_t statems;
    uint64_t gpid;
};

/**
 * 最多1024个进程，一个毫秒容量为4096
 * @param gen
 * @param gpid
 * @return
 */
int snowflake_generator_init(struct snowflake_generator_s* gen, uint64_t gpid);

/**
 * 最多256个进程，一个毫秒容量为16383
 * @param gen
 * @param gpid
 * @return
 */
int snowflake_generator2_init(struct snowflake_generator2_s* gen, uint64_t gpid);

uint64_t snowflake_generator_gen(struct snowflake_generator_s* gen);

uint64_t snowflake_generator2_gen(struct snowflake_generator2_s* gen);


#endif