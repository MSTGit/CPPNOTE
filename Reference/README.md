#### 引用（Reference）

在C语言中，使用指针（Pointer）可以间接获取，修改某个变量的值。例如

```c++
int main() {
	int age = 10;
	int* p = &age;
	*p = 20;
	cout << age << endl;
	getchar();
	return 0;
}
```

最终，通过打印，得到的结果是20，说明通过指针*p成功修改掉了age的值，所以说我们可以利用指针，间接去修改变量的值。

在C++中，使用引用（Reference）可以起到跟指针类似的功能，在C++中，可以通过这种方式来创建一个引用

```C++
int main() {

	int age = 10;
	//定义了一个age的引用refAge
	int& refAge = age;
	refAge = 20;
	cout << age << endl;
	getchar();
	return 0;
}
```

当把程序运行起来以后，控制台打印出的结果为20，说明通过引用修改掉了变量age的值。所以从表面来看，C++中的引用于C语言中的指针很相似。

但是引用也有如下一些注意点：

> 1. 引用相当于是变量的别名（基本数据类型，枚举，结构体，类，指针，数组等，都可以有引用）
> 2. 对引用做计算，就是对引用所指向的变量做计算。refAge += 30等价于age += 30
> 3. 在定义的时候就必须初始化，一旦指向了某个变量，就不可以改变，“从一而终”
> 4. 可以利用引用初始化另外一个引用，相当于某个变量的多个别名

通过一个交换两个数的例子来看一下，引用于指针在写法上的区别

指针

```C++
void swap(int* v1, int* v2) {
	int tmp = *v1;
	*v2 = *v1;
	*v1 = tmp;
}
int main() {
	int a = 10;
	int b = 20;
	swap(a, b);
	getchar();
	return 0;
}
```

引用

```C++
void swap(int& v1, int& v2) {
	int tmp = v1;
	v2 = v1;
	v1 = tmp;
}
int main() {
	int a = 10;
	int b = 20;
	swap(a, b);
	getchar();
	return 0;
}
```

#### 引用的本质

引用的本质就是指针，只是编译器削弱了它的功能，所以引用就是弱化了的指针

接下来我们就来证明引用的本质就是指针：

首先，有以下的一段代码

```C++
int main() {
	int age = 10;
	int* p = &age;
	*p = 30;

	int& ref = age;
	ref = 40;
	getchar();
	return 0;
}
```

先来看一下，一个指针占用多大的内存空间，我们可以利用关键字sizeof(p)来看一下。在我们编译环境为x64架构环境，因此得出在当前环境下，一个指针占用8个字节的空间。

但是当使用sizeof(ref)来获得一个引用所占用的空间时，得到的结果为4。根据前面的结论，引用的本质是指针，那得到的结果应该为8才对。原因是这样的，在前面说到，引用相当于是变量的别名，所以在使用sizeof(ref)时，本质是去获取变量age所占用的存储空间，即sizeof(age)。这样最终得出的结果是4。所以通过这种方式去获取一个引用占用的内存空间是不正确的。

那可以换一个方式来证明，通过定义一个结构体，然后计算结构体所占用的存储空间，来获得一个引用所占用的内存大小。因此先试一下当结构体只有一个int类型的变量时，所占用的存储空间

```C++
struct Student {
	int age;
};
int main() {
	cout << sizeof(Student) << endl;
	getchar();
	return 0;
}
```

通过上面这段程序，在控制台得到的结果为4，说明当前结构体占用的内存空间为4。那现在将age变量改为*age指针变量后

```C++
struct Student {
	int *age;
};
int main() {
	cout << sizeof(Student) << endl;
	getchar();
	return 0;
}
```

运行程序后，在控制台中得到的结果为8，与期望的值一样，因为一个指针变量占用8个直接的内存空间。现在，再将*age指针变量改为&age引用以后

```C++
struct Student {
	int &age;
};
int main() {
	cout << sizeof(Student) << endl;
	getchar();
	return 0;
}
```

运行程序以后，最终在控制台得到的结果，也是8.从侧面证明了，一个引用变量占用8个直接的存储空间。说明引用占用的内存空间与指针一样。

以上的证明，不具有说服力，那再从汇编的角度来证明，引用的本质就是指针，所以通过以下两段代码，查看最终生成的汇编代码

代码一：指针

```C++
int main() {
	int age = 10;
	int* p = &age;
	*p = 30;

	getchar();
	return 0;
}
```

生成的汇编代码为

![1573049671376](https://github.com/MSTGit/CPPNOTE/blob/master/Reference/Resource/1573049671376.png)

然后再看引用的代码；

代码二：引用

```C++
int main() {
	int age = 10;

	int& ref = age;
	ref = 30;
	getchar();
	return 0;
}
```

生成的汇编代码为

![1573049421429](https://github.com/MSTGit/CPPNOTE/blob/master/Reference/Resource/1573049421429.png)

通过仔细对比我们发现，指针和引用生成的汇编代码与机器码是完全一样的。所以可以得出结论：**引用的本质就是指针**