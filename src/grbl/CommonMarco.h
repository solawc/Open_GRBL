#ifndef __CommonMarco_h
#define __CommonMarco_h

#include "../main.h"

/**************************************************
 * This is a library for all task and connect
 * 
 * Update:
 * - 2022-06-28 
 * ***********************************************/


/*************************************************
 * __ValueMonitor(now, func)
 * - 用于监控变量，当变量改变时，触发一个事件
 * - now  被监控的变量（输入整形）
 * - func 时间回调函数
 * **********************************************/
#define __ValueMonitor(now, func) \
do{ \
    static int last = (now); \
    if(last != (now)) func, last=(now); \
} while(0);
#define __EventMonitor(now, func) __ValueMonitor((now), func)


/**************************************************
 *让一个变量增加或者减去一个值，在大于等于最大值后从0开始，低于0后从最大值开始
 *src:   被控变量
 *step:  增加或者减少的值
 *max:   最大值
 *无
 **************************************************/
#define __ValueStep(src, step, max) ((src)=(((step)>=0)?(((src)+(step))%(max)):(((src)+(max)+(step))%(max))))

/**************************************************
 * 让一个变量增加或者减去一个值，在大于最大值后从最小值开始，小于最小值后从最大值开始
 * src:被控变量
 * plus:增加的值
 * min:最小值
 * max:最大值
 * 无
 *************************************************/
#define __ValuePlus(src, plus, min, max)\
do{\
    int __value_temp = (src);\
    __value_temp += (plus);\
    if(__value_temp<(min))__value_temp=(max);\
    else if(__value_temp>(max))__value_temp=(min);\
    (src) = __value_temp;\
}while(0)


/*************************************************
 *非阻塞式间隔指定时间执行一个函数
 *func:被执行函数(可以是赋值等其他语句)
 *time:设定间隔时间(ms)
 *无
 *************************************************/
#define __IntervalExecute(func, time) \
do{\
    static unsigned long lasttime=0;\
    if(millis()-lasttime>=(time))func,lasttime=millis();\
}while(0)


/*************************************************
 * 将一个函数重复调用指定次数
 * func:被调用函数(可以是赋值等其他语句)
 * n:重复调用次数
 * 无
 *************************************************/
#define __LoopExecute(func, n) for(unsigned long i=0;i<(n);i++)func

#ifndef constrain
#   define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#endif


/*************************************************
 * 将一个值限制在一个范围内
 * x:被限制的值(任意类型)
 * min:最小值(任意类型)
 * max:最大值(任意类型)
 * 无
 *************************************************/
#define __LimitValue(x, min, max) ((x)=constrain((x),(min),(max)))

/*************************************************
 * 将一个值的变化区间线性映射到另一个区间
 * x:被映射的值(任意类型)
 * in_min:被映射的值的最小值
 * in_max:被映射的值的最大值
 * out_min:被映射的值的最小值
 * out_max:被映射的值的最大值
 * 映射值输出
 *************************************************/
#define __Map(x, in_min, in_max, out_min, out_max) \
    (((x)-(in_min))*((out_max)-(out_min))/((in_max)-(in_min))+(out_min))

/*************************************************
 * 获取一个数组的元素个数
 * arr:数组名(任意类型)
 * 这个数组的元素个数
 *************************************************/
#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))

/*************************************************
 * 将一个值强制按指定类型解释，常用于结构体拷贝
 * type:类型名(任意类型)
 * data:被解释的数据(任意类型)
 * 解释输出
 *************************************************/
#define __TypeExplain(type, data) (*((type*)(&(data))))

/*************************************************
 * 执行一个函数在不超时的情况下直到函数的返回值为指定值
 * func:被调用函数
 * n:希望函数的返回值
 * timeout:超时时间
 * flag:外部提供变量，用于检查是否超时
 * 无
 * ***********************************************/
#define __ExecuteFuncWithTimeout(func, n, timeout, flag)\
do{\
    volatile unsigned long start=millis();\
    (flag)=false;\
    while(millis()-start<(timeout)){\
        if(func==(n)){(flag)=true;break;}\
    }\
}while(0)

/*************************************************
 * 函数只执行一次，常用于初始化
 * func:被调用函数(也可以是赋值等其他语句)
 * 无
 ************************************************/
#define __ExecuteOnce(func)\
do{\
    static bool isInit = false;\
    if(!isInit){func,isInit=true;}\
}while(0)

/*************************************************
 * 获取信号量，当sem为true时执行一次func
 * sem:信号量(bool类型)
 * func:被调用函数(也可以是赋值等其他语句)
 * 无
 ************************************************/
#define __SemaphoreTake(sem, func)\
do{\
    if((sem)){func,(sem)=false;}\
}while(0)

#endif
