我们知道，在C语言当中，是不支持函数重载的，但是C++支持函数重载，并且有很多语言都支持函数重载。

例如下列的两个函数，函数名相同，参数的个数不同，就构成了函数的重载

```C++
int sum(int v1, int v2) {
	return v1 + v2;
}

int sum(int v1, int v2, int v3) {
	return v1 + v2 + v3;
}
```

当参数个数不同，但是参数的类型不同时，也可以构成重载。例如

```C++
void func(int v1, double v2) {
}

void func(double v1, int v2) {

}
```



#### 函数重载的规则

1. 函数名相同
2. 参数的个数不同
3. 参数的类型不同
4. 参数的顺序不同

注意以下情况，不能构成函数重载

1.返回值类型与函数重载无关，例如下列的两个函数

```c++
void func(int v1, double v2) {
}

double func(int v1, double v2) {
	return 0;
}
```

上面的两个函数，不构成函数的重载，在编译器中，会直接标错[下图]，代码不能通过。

![1572750509913](https://github.com/MSTGit/CPPNOTE/blob/master/Overload/Resource/1572750509913.png)

我们想想为什么这种情况下不能构成重载？

因为这样会有歧义，有二义性。加入上面两个函数可以构成函数重载，那么我们通过下列方法调用函数时，最终应该调用哪个方法呢？

```c++
int main() {
	func(10, 10.5);
	getchar();
	return 0;
}
```

难道不觉得调用这两个函数都合理吗？这样就导致有歧义，不能构成重载、

2.调用函数时，实参的隐式类型转换可能会产生二义性，例如下列的三个函数

```C++
void display(long a) {
	cout << "display(long) -" << a << endl;
}

void display(double a) {
	cout << "display(double) -" << a << endl;
}

void display(int a) {
	cout << "display(int) -" << a << endl;
}
```

如果我们通过这种方式来进行调用的话，是可以分别调用成功的

```C++
int main() {

	display(10);
	display(10L);
	display(10.0);
    
	getchar();
	return 0;
}
```

但是，当我们去掉函数`void display(int a)`以后，会发现我们程序就报错了。

![1572751436197](https://github.com/MSTGit/CPPNOTE/blob/master/Overload/Resource/1572751436197.png)

因为此时编译器发现，`display(10)`调用函数`void display(long a)`合理，调用函数`void display(double a)`也是合理的。因为这个时候调用`display(10)`时，传入的参数存在隐式转换。因为我们平时就可以将一个int类型赋值给一个long类型，也可以将一个int类型赋值给一个double类型，例如这样去写代码

```C++
long l = 10;
double d = 10;
```

上面这种写法，其实是有一个转换操作，编译器自动将int类型转为了long/double类型。因此当我们去掉函数`void display(int a)`以后，通过`display(10)`调用两个函数都是合理的，因此又产生了二义性，所以编译器会给出错误的提示，所以这种情况也不构成函数的重载。

#### 函数重载的本质

为什么C++支持函数重载，而C语言不支持函数重载呢？本质是采用了name mangling或者叫name decoration技术

> C++编译器默认会对符号名（比如函数名）进行改编，修饰；有些地方翻译为“命名倾轧”

同样的假设我们有以下三个函数

```c++
void display(long a) {
	cout << "display(long) -" << a << endl;
}

void display(double a) {
	cout << "display(double) -" << a << endl;
}

void display(int a) {
	cout << "display(int) -" << a << endl;
}
```

编译器会对这三个函数重载的函数进行name mangling的操作。我们从表面上看函数名叫做`display`，但是编译器会分别对函数名进行改编修饰。例如函数`void display(int a)`在真正编译的时候，函数名可能变为了`display_int`，函数`void display(long a)`在真正编译的时候，函数名可能变为了`display_long`，函数`void display(double a)`在真正编译的时候，函数名可能变为了`display_double`，改编后的会变为一个新的函数名，而这个新的函数名，会包含参数信息。这样的话，就能保证三个函数，可以共同存在。

但是，在不同的编译器（MSVC,g++）有不同的生成规则，因此最终函数会被改编成什么样，是根据编译器的规则来进行的。

##### 证明函数重载的本质

我们可以利用反汇编，来看一下构成函数重载的函数，在运行是，最终转成的汇编代码

我们新增一个无参的函数以后，在main函数中调用该函数，并且在调用哈数的地方打上一个断点，然后将程序运行起来。

```java
void display(long a) {
	cout << "display(long) -" << a << endl;
}

void display(double a) {
	cout << "display(double) -" << a << endl;
}

void display(int a) {
	cout << "display(int) -" << a << endl;
}

void display() {
	cout << "display() -"<< endl;
}
```

![1572753062883](https://github.com/MSTGit/CPPNOTE/blob/master/Overload/Resource/1572753062883.png)

运行起来以后，在编译器代码区右击鼠标，选择转到反汇编，我们就可以来到当前代码转为的汇编代码

![1572753479949](https://github.com/MSTGit/CPPNOTE/blob/master/Overload/Resource/1572753479949.png)

首先我们知道，每一条汇编指令都有自己对应的内存地址，并且是按顺序往下执行的，并且连续的汇编指令，对应的地址也是连续的。

我们从上图中看到，对应在代码中的函数调用，转到汇编以后，call指令调用的函数名也是一样的。这和我们预想的结果有点不一样。但是有一点不一样，就是在call指令调用display时，括号内的东西不一样，那这里面的东西是什么呢？这其实是调用对应函数的内存地址，因此我们发现，在调用函数时，虽然看到call指令调用的函数名好像都是display，但是调用的地址却不一样，因此我们推断，调用的函数并不是同一个函数。

因此我们可以借助一个工具 IDA Pro来查看我们代码打包成可执行文件后的反汇编代码。并且将我们C++编译器的模式设置为Release模式，再关闭编译器的优化功能。

最终反编译后，我们看到main函数是这样的

![1572755029840](https://github.com/MSTGit/CPPNOTE/blob/master/Overload/Resource/1572755029840.png)

并且我们看到左边有4个不同的display函数名，我们可以看一下这4个函数的具体实现，最终我们发现

![1572755196408](https://github.com/MSTGit/CPPNOTE/blob/master/Overload/Resource/1572755196408.png)

![1572755225438](https://github.com/MSTGit/CPPNOTE/blob/master/Overload/Resource/1572755225438.png)

![1572755252469](https://github.com/MSTGit/CPPNOTE/blob/master/Overload/Resource/1572755252469.png)

![1572755289810](https://github.com/MSTGit/CPPNOTE/blob/master/Overload/Resource/1572755289810.png)

所以我们看到，最终的函数名是不一样的

而且，我们还发现，函数名称的生成顺序和我们函数定义的顺序是一样的。

因此，我们证明了上面说的，C++函数重载，使用了name mangling技术。