#ifndef snowflake_H
#define snowflake_H


#include <stdint.h>
#include <sys/time.h>


#define SNOWFLAKE_EPOCH 1538006400000

#define BASE_ATTR \
    uint64_t statems;\
    uint64_t gpid;

struct snowflake_s {
    BASE_ATTR
};

struct snowflake2_s {
    BASE_ATTR
};

struct id32 {
    uint32_t cnt;
    uint32_t gpid;
};

/**
 * 最多1024个进程，一个毫秒容量为4096
 * @param sf struct snowflake_s*
 * @param gpid uint64_t
 */
void snowflake_init(struct snowflake_s* sf, uint64_t gpid);

/**
 * 最多256个进程，一个毫秒容量为16383
 * @param sf struct snowflake2_s*
 * @param gpid uint64_t
 */
void snowflake2_init(struct snowflake2_s* sf, uint64_t gpid);

/**
 * 非线程安全
 * @param sf struct snowflake_s*
 * @return uint64_t
 */
uint64_t snowflake_nts_gen(struct snowflake_s* sf);

/**
 * 非线程安全
 * @param sf struct snowflake2_s*
 * @return uint64_t
 */
uint64_t snowflake2_nts_gen(struct snowflake2_s* sf);

/**
 * 线程安全
 * @param sf struct snowflake_s*
 * @return uint64_t
 */
uint64_t snowflake_gen(struct snowflake_s* sf);

/**
 * 线程安全
 * @param sf struct snowflake2_s*
 * @return uint64_t
 */
uint64_t snowflake2_gen(struct snowflake2_s* sf);

/**
 *
 * @param id32
 * @param gpid
 */
void id32_init(struct id32* id, uint32_t gpid);

uint32_t id32_gen(struct id32* id);

#endif