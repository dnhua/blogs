> C语言的申明总是令人头大，对于这块内容也一直让我头疼。希望通过这篇博客能够稍微梳理一下。材料和例子来源于《C专家编程》

# 一、C语言的申明的优先级规则

先来个例子，看看下面这行C代码到底是个啥玩意儿：

```c
char * const *(*next)();
```

## 1.1 优先级规则

* A 申明从它的名字开始读取，然后按照优先级顺序依次读取。
* B 优先级从高到低依次是： 
	* B.1 声明中被括号括起来的那部分
	* B.2 后缀操作符：
		  括号()表示这是一个函数，而方括号表示这是一个数组。
	* B.3 前缀操作符：星号*表示  指向...的指针。
* C 如果const和(或)volatile关键字的后面紧跟类型说明符（如int，long等），那么它作用于类型说明符。在其它情况下，const和(或)volatile关键字作用于它紧邻的指针星号。

## 1.2 分析 char * const *(*next)();

1. 首先，看变量名是“next”，并注意到它直接被括号括住（A）
2. 把括号括住的东西看作一个整体(*next)，得出 “next是一个指向...的指针”（B.1）
3. 然后考虑括号外面的东西，在星号前缀和括号后缀之间做出选择：
   B.2规则告诉我们优先级较高的是右边的函数括号，所以得出“next是一个函数指针，指向一个返回...的函数”（B.2）
4. 然后，处理前缀*号，得出指针所指的内容（B.3）
5. 最后，把“char * const”解释为指向字符的常量指针

所以最后得出：next是一个指针，它指向一个函数，该函数返回另一个指针，该指针指向一个类型为char的常量指针。
虽然能够搞明白，并且有规则可循。但还是不得不吐槽，C的申明也太复杂了。哎~~~

# 二、typedef

## 2.1 使用typedef为你的申明做简化

看系统调用signal函数的申明：

```c
void (*signal(int sig, void(*func)(int)))(int);
```
先不看signal括号里面的东西：

```c
void (*signal(         ))(int);
```
可以看出来，signal是一个函数，然后它返回一个指针；该指针所指向的函数接受一个int参数，并返回void。我们再来看signal括号里面的东西，第一个参数不用解释，来看第二个参数：

```c
void(*func)(int)
```
不难看出func是一个函数指针，指向的函数接受一个int参数，返回void。接下来让我们用typedef来简化它：

```c
/* ptr_ti_func是一个函数指针，该函数接受一个int参数，返回void。 */
typedef void(*ptr_to_func) (int)	
//接着再申明之前的那个signal
ptr_to_func signal(int, ptr_to_func);
```
## 2.2 typedef VS #define

\#define只是做替换而已；而typedef是真正的封装--申明它之后，不能再往里面增加东西。举两个例子：

例子1：
```c
#define myInt int
usigned myInt i;	//可以没问题，就是文字替换而已：unsigned int i;
typedef int myInt;
usigned myInt i;	//非法，不可以在myInt里面加usigned了。
```

例子2：
```c
#define int_ptr int *
int_ptr a,b;		//a是int *类型，b是一个int;
typedef int * int_ptr;
int_ptr a,b;		//a和b都是int *类型。
```

最后想说一下作者本身对这个也只是初步了解，如有理解错误欢迎反馈！！


> See you next time. Happy Coding!!!
**[我的github](https://github.com/dnhua)**


