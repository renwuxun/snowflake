## Snowflake ID generator
雪花ID生成器

#### 第一种：snowflake_s
ttttttttttttttttttttttttttttttttttttttttttssssssssssssmmmmmmmmmm
最多1024个线程，一个毫秒容量为4096

#### 第二种：snowflake2_s
ttttttttttttttttttttttttttttttttttttttttttssssssssssssssmmmmmmmm
最多256个进程，一个毫秒容量为16383

* t：毫秒时间戳，42位
* s：时间点计时器，12/14位
* m：全局线程id，10/8位

当计数器满后，会自动累积到下个时间戳，且不会导致id回退
