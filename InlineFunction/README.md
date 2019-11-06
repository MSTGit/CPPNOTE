#### 内联函数（inline function）

使用inline修饰函数的**声明**或者**实现**，可以使其变成内联函数。一般建议声明和实现都增加inline修饰。

假设我们现在有如下的两个函数，使用inline来进行修饰，并且在main函数中进行调用

```C++
inline void func() {
	cout << "func()" << endl;
}

inline int sum(int v1, int v2) {
	return v1 + v2;
}

int main() {
	func();

	int c = sum(10, 20);
	cout << c << endl;
	getchar();
	return 0;
}
```

我们将程序运行起来以后，发现最终运行的结果与没有使用inline修饰的函数效果一样，感觉不到任何区别。那么使用inline修饰的函数到底有什么作用呢？

使用inline修饰的函数有以下特点：

- 编译器会将函数调用直接展开为函数体代码；即最终编译器在编译代码时，会将上面代码转换为下列的形式

  ```C++
  int main() {
  	cout << "func()" << endl;
  
  	int c = 10 + 20;
  	cout << c << endl;
  	getchar();
  	return 0;
  }
  ```

  通过这样转换，就成为内联函数。那么这种转换有什么用呢？

- 可以减少函数调用的开销；因为在代码编译时，直接将函数调用展开为函数体代码，就不存在函数调用，因此不存在函数调用的开辟栈空间和回收栈空间操作。

- 代码体积会增大。例如有以下代码

  ```c++
  inline void func() {
  	cout << "func1()" << endl;
  	cout << "func2()" << endl;
  	cout << "func3()" << endl;
  }
  int main() {
  	func();
  	func();
  	func();
  	getchar();
  	return 0;
  }
  ```

  在代码编译阶段，编译器会将代码转换为

  ```C++
  int main() {
  	cout << "func1()" << endl;
  	cout << "func2()" << endl;
  	cout << "func3()" << endl;
  	cout << "func1()" << endl;
  	cout << "func2()" << endl;
  	cout << "func3()" << endl;
  	cout << "func1()" << endl;
  	cout << "func2()" << endl;
  	cout << "func3()" << endl;
  	getchar();
  	return 0;
  }
  ```

     

那么，我们在什么时候去使用内联函数呢？一般满足下列情况时，可以考虑使用内联函数。

1. 函数代码体积不大
2. 频繁调用的函数

但是，在使用内联函数时，也需要注意以下问题；

1. 尽量不要内联超过10行代码的函数
2. 有些函数即使声明为inline，也不一定会被编译器内联，比如递归函数

因此关键字inline可以理解为，仅仅是建议编译器在代码编译的时候，将函数变为内联函数，但是最终是否会变为内联函数，则需要看编译器的优化规则。

既然inline可以让函数变为内联函数，但是从表面也看不出差别，那么我们就来证明一下内联确实存在。

#### 窥探内联的本质

首先，我们看以下，如果是普通函数[如下]，最终生成的汇编代码是怎样的。

```C++
int sum(int v1, int v2) {
	return v1 + v2;
}
void func() {
	cout << "func()" << endl;
}
int main() {
	
	func();
	int c = sum(10, 20);
	cout << c << endl;
	return 0;
}
```

代码运行起来以后，我们转代反汇编的结果为

![1572962553358](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572962553358.png)

从上图的汇编代码，我们看到有两条call指令，分别调用了函数func和函数sum。接下来，我们尝试将函数sum和函数func都变为内联函数。

```C++
inline int sum(int v1, int v2) {
	return v1 + v2;
}
inline void func() {
	cout << "func()" << endl;
}
int main() {
	
	func();
	int c = sum(10, 20);
	cout << c << endl;
	return 0;
}
```

代码运行起来以后，我们来看看最终生成的汇编代码

![1572962791117](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572962791117.png)

我们看到，加了inline修饰后的函数，仍然使用了call指令，存在函数调用，并不是我们我们前面说理解的，直接将函数体代码展开。原因是我们现在编译器处于debug模式，在debug模式下，编译器默认是不会内联的，因为内联是做优化，因此我们需要做一些操作，将编译器修改为release模式，并去掉内联

```C++
int sum(int v1, int v2) {
	return v1 + v2;
}
void func() {
	cout << "func()" << endl;
}
int main() {
	
	func();
	int c = sum(10, 20);
	cout << c << endl;
	return 0;
}
```

重新运行代码，得到的汇编为

![1572963250663](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572963250663.png)

我们看到，此时没有看到call指令调用func函数与sum函数。并且我们注意到有一个push 1Eh的操作。在16进制里面1Eh等价于10进制的30.所有我们看到，此时是直接将30push到栈里面，连加法的操作都不存在了，这是因为在release模式下，编译器默认会做最大的优化，所以会省略很多细节。但是，我们还是没看到Inline的作用，所以我们现在还需要多编译器进行配置，修改编译器的优化力度，进制编译器优化[下图]

![1572964048190](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572964048190.png)

修改配置以后，我们再次运行程序，最终得到的汇编代码为

![1572963833701](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572963833701.png)

现在，在没有inline时，release模式下，我们看到存在函数调用。

在当前编译器配置 模式下，我们将函数加上inline关键字后

```C++
inline int sum(int v1, int v2) {
	return v1 + v2;
}
inline void func() {
	cout << "func()" << endl;
}
int main() {
	
	func();
	int c = sum(10, 20);
	cout << c << endl;
	return 0;
}
```

运行程序，得到如下的汇编代码

![1572964222158](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572964222158.png)

我们看到，这次的结果与以前不一样了，首先不存在函数调用func与sum函数了，并且从sum可以看到mov指令将0Ah放入寄存器ecx中，然后又做了add操作，其中0Ah为10进制的10,14h为10进制的20，add操作完成后将结果又存入了ecx中，此时ecx中的值是30，接下来又做了一次mov操作，将ecx的值存入变量c。执行完指令以后c的值为30。最终将30打印输出。

并且如果我们将func函数中的函数体手动进行展开

```C++
inline int sum(int v1, int v2) {
	return v1 + v2;
}
int main() {
	
	cout << "func()" << endl;
	int c = sum(10, 20);
	cout << c << endl;
	return 0;
}
```

我们看看最终生成的汇编代码

![1572966541023](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572966541023.png)

发现通过func通过函数调用和直接将函数体展开，最终生成的汇编代码是相同的，因此就说明两种代码是等价的。

所以通过上面的结论，我们可以看到，通过inline修饰的函数，在程序编译阶段，确实会对代码进行优化。

但是如果我们对递归函数进行内联的话，最终编译器会优化吗？

```C++
inline void run() {
	run();
}
int main() {
	run();
	return 0;
}
```

将程序运行以后，得到的汇编代码为

![1572966818454](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572966818454.png)

从生成的汇编代码，看到依然存在函数调用，所以在存在递归的情况下，函数是不会被内联的。

----

另外，我们也可以从最终生成的可执行文件来证明inline确实是对代码进行了优化。

如果我们将sum和func函数去掉inline后，通过IDA读取可执行文件

我们看到，最终生成的函数有sum与func

![1572967556979](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572967556979.png)

我们在看看sum，func，main函数中的实现

![1572967676506](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572967676506.png)

![1572967714247](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572967714247.png)

![1572967752591](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572967752591.png)

可以看到，在没有通过inline来修饰函数时，代码是没有进行优化的。

当我们用inline修饰以后，得到的可执行文件，首先我们看到，从函数名称角度，就不一样了，现在只有一个main函数。

![1572967946754](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572967946754.png)

我们在看看main函数里面的实现

![1572968113460](https://github.com/MSTGit/CPPNOTE/blob/master/InlineFunction/Resource/1572968113460.png)

我们看到，最终是在main函数里面，不存在func于sum函数的call操作，直接调用的打印func()与做加法操作。不存在函数调用。因此，从可自行文件角度，也可以得出，使用inline修饰的函数，在程序编译阶段，确实会对代码进行优化。

#### 内联函数与宏的区别

1. 内联函数与宏都可以减少函数调用的开销
2. 对比宏，内联函数多了语法检查和函数特性

但是由于宏是简单的文本替换，因此在一些情况下还是存在一些区别，例如下列的两段代码

```C++
#define sum(x) (x + x)
int main() {
	int a = 10;
	int b = sum(++a);
	return 0;
}
```

```
 inline int sum(int x) {
	 return x + x;
 }
int main() {
	int a = 10;
	int b = sum(++a);
	return 0;
}
```

你能知道最终两段代码最终的结果分别为多少吗？