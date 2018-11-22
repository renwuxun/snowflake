## Snowflake ID generator
生成雪花id，非线程安全
#### 第一种：snowflake_generator_s
ttttttttttttttttttttttttttttttttttttttttttmmmmmmmmmmssssssssssss
最多1024个进程，一个毫秒容量为4096

#### 第二种：snowflake_generator2_s
ttttttttttttttttttttttttttttttttttttttttttmmmmmmmmssssssssssssss
最多256个进程，一个毫秒容量为16383

* t：毫秒时间戳，42位
* m：全局进程id，10/8位
* s：时间点计时器，12/14位

