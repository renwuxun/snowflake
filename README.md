## Snowflake ID generator
雪花ID生成器

#### 第一种：snowflake_s
mmmmmmmmmmttttttttttttttttttttttttttttttttttttttttttssssssssssss
最多1024个进程，一个毫秒容量为4096

#### 第二种：snowflake2_s
mmmmmmmmttttttttttttttttttttttttttttttttttttttttttssssssssssssss
最多256个进程，一个毫秒容量为16383

* m：全局进程id，10/8位
* t：毫秒时间戳，42位
* s：时间点计时器，12/14位

