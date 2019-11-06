#### const

**const是常量的意思，被其修饰的变量不可修改**

我们在定义普通局部变量的时候，通常是这样来进行定义的

```C++
int main() {
	int age = 10;
	age = 20;
	getchar();
	return 0;
}
```

我们在定义的时候，为其赋了初始值然后我们可以在后面需要修改变量值的地方，进行修改，比如我们后面将age的值修改为20；

但是通过const修饰的变量，是不可以修改的，因此不可以以这种方式来编写程序

```C++
int main() {
	const int age = 10;
	age = 20;
	getchar();
	return 0;
}
```

这样编写程序，编译器会提示错误。

![1573040159804](https://github.com/MSTGit/CPPNOTE/blob/master/const/Resource/1573040159804.png)

并且也不允许在定义的时候不赋初始值，在后面使用到的地方在赋初始值，因此下面这种方式也是错误的。

```C++
int main() {
	const int age;
	age = 20;
	getchar();
	return 0;
}
```

这样编写程序，编译器同样会提示错误。

![1573040339697](https://github.com/MSTGit/CPPNOTE/blob/master/const/Resource/1573040339697.png)

**如果const修饰的是类，结构体（的指针），其成员变量也不可以修改**。例如下面的这种写法也是错误的

```C++
struct Date {
	int year;
	int month;
	int day;
};

int main() {
	const Date d = {2011, 2, 5};
	d.year = 2015;
	return 0;
}
```

编译器也会报错

![1573040771169](https://github.com/MSTGit/CPPNOTE/blob/master/const/Resource/1573040771169.png)

了解完const以后，我们来看看一个有趣的问题。以下5个指针，分别代表什么含义？

```C++ 
int age = 10;
const int *p0 = &age;
int const *p1 = &age;
int * const p2 = &age;
const int * const p3 = &age;
int const * const p4 = &age;
```

上面的指针问题，可以用以下结论来解决

**const修饰的是其右边的内容**

因此，假设我们有下面的这段代码

```C++
int main() {
	int age = 10;
	int height = 30;
	int age = 10;
	const int* p0 = &age;
	int const* p1 = &age;
	int* const p2 = &age;
	const int* const p3 = &age;
	int const* const p4 = &age;
	*p2 = 20;
	p2 = &height;
	*p2 = 40;
	getchar();
	return 0;
}
```

我们发现，最终报错的是p2，*p2没有报错

![1573041673002](https://github.com/MSTGit/CPPNOTE/blob/master/const/Resource/1573041673002.png)

原因是现在const修饰的是p2，所以现在p2是常量，但是*p2不是常量，最终的结果就是 *p2可以赋值，p2不可以赋值。

如果我们现在将上面代码的下面部分

```C++
*p2 = 20;
p2 = &height;
*p2 = 40;
```

p2修改为p0的话。现在哪些地方会报错呢？

同样的，利用我们前面的结论，我们知道，现在const修饰的是*p0是常量，p0不是常量，所以 *p0不能被赋值，因此修改 *p0的地方都会报错

![1573042199595](https://github.com/MSTGit/CPPNOTE/blob/master/const/Resource/1573042199595.png)

另外，p0和p1其实是一样的，const修饰的都是*p0和 *p1,因此两个没区别，同理`const int * const p3 = &age`与`int const * const p4 = &age`也是等价的。两个const中前面的一个修饰 *p3与 *p4，后面的一个修饰p3,p4,因此p3,p4, *p3, *p4均为常量。