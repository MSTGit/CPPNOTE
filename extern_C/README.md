**被extern "C"修饰的代码会按照C语言的方式去编译。**

看到这句话，可能有点懵，那么我们就来看看这句话是什么意思。

首先，如果我们在C++的文件中定义了以下两个函数

```C++
void func() {

}
void func(int v) {
}
```

那么，最终两个函数会按照C++的方式进行编译。如果我们对两个函数使用extern "C"进行修饰的话

```C++
extern "C" void func() {

}
extern "C" void func(int v) {
}
```

接下来，我们尝试将程序运行起来。我们可以发现，最终编译器报错了

![1572872564089](C:\Users\T\AppData\Roaming\Typora\typora-user-images\1572872564089.png)

说明上面的两个函数是有问题的。我们在前面章节介绍使用C++的函数重载时，是可以正常运行的。那么为什么会报错？是因为我们现在是使用C语言的方式进行编译上面的两个函数，在C语言中，不支持函数重载，因此编译器给出了错误提示。

我们还可以使用另外的一些方式来让大括号以内的代码，都按照C语言的方式进行编译，如

```C++
extern "C" {
	void func() {

	}
	void func(int v) {
	}
}

extern "C" {
	void func();
	void func(int v);
}
```

**如果函数同时有声明和实现，要让函数声明被extern “C”修饰，函数实现可以不修饰**

很多时候，我们编写的函数，是分声明和实现的，例如我们会把函数声明写在文件的前面，把函数的实现写在文件的后面，例如

```C++
extern "C" void func();
void func() {

}
```

#### extern "C"的作用

由于C，C++编译规则的不同，在C，C++混合开发时，可能会经常出现以下操作

在使用第三方框架/库时，可能是用C语言写的开源库。我们来模拟这样一种场景，我们在一个.c的文件中定义了一下一些函数

```c
int sum(int v1, int v2) {
	return v1 + v2;
}

int delta(int v1, int v2) {
	return v1 - v2;
}
```

如果此时，想要在C++代码中使用的话，可以将这些函数声明一份到C++调用的地方，例如

```C++
int sum(int v1, int v2);
int delta(int v1, int v2);
int main() {
	sum(10, 20);
	delta(30, 20);

	getchar();
	return 0;
}
```

这样我们就可以调用到.c文件中的两个方法了。现在看起来，是合情合理的。但是当我们将程序运行起来以后，程序给出了错误信息

![1572874658530](C:\Users\T\AppData\Roaming\Typora\typora-user-images\1572874658530.png)

这是为什么呢？我们既有函数的声明，又有对应声明的实现。原因是我们现在是在C++当中调用的两个函数，最终编译的时候，编译器是按照C++的方式去寻找对应函数的实现，C与C++是按照不同的方式进行编译的，因此会出现找不到的情况。这个时候，我们就需要告诉编译器，让两个函数按照C语言的方式进行编译与查找。我们可以这样去修改

```c++
extern "C" {
	int sum(int v1, int v2);
	int delta(int v1, int v2);
}
int main() {
	sum(10, 20);
	delta(30, 20);

	getchar();
	return 0;
}
```

可以发现，最后程序编译成功了。但是，如果我们的第三方库这样写，是不合理的，因为如果别人要使用你框架内的函数时，需要将声明拷贝到需要使用到的文件顶部。这样很麻烦，因此，我们需要新加一个.h文件。用来专门放置我们.c文件中函数声明，因此我们这里新建了一个math.h的头文件。这样，别人在使用到我们写的框架时，就只需要这样导入我们的头文件就可以了

```C++
extern "C" {
#include "math.h"
}
int main() {
	sum(10, 20);
	delta(30, 20);

	getchar();
	return 0;
}

```

**#include 的作用**

相当于是将include文件中的内容，直接拷贝到声明include的地方。因此这两种写法是等价的

```C++
extern "C" {
#include "math.h"
}
extern "C" {
	int sum(int v1, int v2);
	int delta(int v1, int v2);
}
```

这样就解决了C++调用C语言函数的问题，不过还是比较麻烦，别人在应用你函数的时候，需要自己去告诉编译器，将对应的文件按照C语言的方式进行编译，并且extern "C"在C语言环境下，因此为了解决这个兼容的问题，我们需要使用条件编译告诉编译器，如果是在C++ 的环境下，自动为.h中声明的函数自动加上extern "C"，C语言时就不加。所以我们可以这样进行改进。

```c
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	int sum(int v1, int v2);
	int delta(int v1, int v2);
#ifdef __cplusplus
}
#endif // __cplusplus
```

那么，现在回到我们的main.cpp文件当中，我们只需要这样声明就可以调用C语言文件中的函数了

```C++
#include "math.h"
int main() {
	sum(10, 20);
	delta(30, 20);

	getchar();
	return 0;
}
```

##### #pragma once

我们经常使用#define，#ifndef，#endif来防止头文件的内容被重复包含

#pragma once可以防止整个文件的内容被重复包含

区别

1. #define，#ifndef，#endif受C/C++标准的支持，不受编译器的任何限制
2. 有些编译器不支持#pragma once(较老编译器不支持，如GCC3.4版本之前)，兼容性不好
3. #define，#ifndef，#endif可以针对文件中的部分代码，而#pragma once只能针对整个文件