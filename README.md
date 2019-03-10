# InlineHookAvertHuorongjian
绕过火绒剑检测的一个简单的inlinehook方法
---
inline hook最简单的就是把函数最前面的一个字节换成0xe9 然后后面四个字节是跳转地地址
但是发现过不了火绒剑的检测
然后就想着检测方法是检测函数第一个字符是不是0xe9 遂把跳转地址往后面移了两字节发现还是不成功
<br>
<br>于是就想着怎么换掉jmp跳转 不用0xe9
* 观测发现在进入MessageBoxA时候 ZF标志位为0所以想到用jz跳转
查询百度发现jnz的机器码为`0x85`但随后发现这是短跳转还是不行
* 正在我一筹莫展之时想起od有汇编功能 输入指令`jnz xxxxxxx`得到机器码 `0F85XXXXXX`后面就是地址之间的距离 //随便找了个软件不用在意
<br>![Image text](https://raw.githubusercontent.com/asmjmp0/InlineHookAvertHuorongjian/master/1.png)
* 于是就按照这种写法最终达到了我的目的详情看代码
<br>![Image text](https://raw.githubusercontent.com/asmjmp0/InlineHookAvertHuorongjian/master/2.png)
<br>就这样了本人只是一名大二的学生代码写的不好的地方请见谅 当然这种写法还是很容易被针对的
`QQ:302864369` `Email:302864369@qq.com`
欢迎各位大佬和我讨论 还有更好的写法
最后：我永远喜欢珂朵莉！！！！！
<br>![Image text](https://raw.githubusercontent.com/asmjmp0/InlineHookAvertHuorongjian/master/3.jpg)
