#### 虚表

在上一篇文章中，对虚函数进行了讨论，Animal的子类继承与Animal，如Cat，在Animal中定义了两个函数，并且在子类中对这些函数进行了重写，然后将创建的对象，通过父类指针来指向该对象，利用父类指针来调用Animal类包含的两个函数，按照默认的情况，通过指针调用函数，最终被调用的是父类中定义的函数，因为在默认情况下，调用函数是只看当前指针的类型。这种情况与平时开发中不常用，更常用的是根据右边真正的对象类型，来调用对象对应的函数。前面的做法是在父类定义定义函数时，使用virtual关键字来修饰，然后将两个函数变为虚函数后，才能实现面向对象的多态。

接下来就探究以下，虚函数的原理是什么，为什么这么神奇。

首先定义如下两个类

```C++
struct Animal {
	int m_age;
	virtual void speak() {
		cout << "Animal::speak()" << endl;
	}

	virtual void run() {
		cout << "Animal::run()" << endl;
	}
};

struct Cat : Animal {
	int m_life;
	void speak() {
		cout << "Cat::speak()" << endl;
	}

	void run() {
		cout << "Cat::run()" << endl;
	}
};

int main() {

	cout << sizeof(Cat) << endl;
	getchar();
	return 0;
}
```

然后现在可以看以下创建出一个Cat对象，需要占用多大的内存空间，如果按照正常的情况，占用的空间是8个字节，现在将程序运行起来后，得到的结果是12个字节。也就是说，如果类中有定义虚函数，那创建出来的对象会多占用4个字节的内存空间。并且发现只要有虚函数，就会多占用4个字节的内存空间，与虚函数的数量无关（≥1），也就意味着，在虚函数的背后，需要这4个字节来实现。没错，这四个字节存储的就是想虚表的地址，首先来了解以下虚函数的原理；

> 虚函数的实现原理是虚表，这个虚表里面存储这最终需要调用的函数地址，这个虚表也叫虚函数表

接下来，假设通过如下的方式创建一个Cat对象，并用Animal指针来指向该对象

```C++
Animal* cat = new Cat();
cat->m_age = 20;
cat->speak();
cat->run();
```

通过这种方式，最终会调用Cat类中的speak方法和run方法，相信这一点是能理解的。接下来就探究以下原理。下图是在x86环境下的虚表示意图

![1574080132439](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574080132439.png)

根据上图与代码，左边的内存地址就是一个cat对象占用的内存空间一共12个字节，其中8个字节用来存放成员变量m_age与m_life，最前面多出来的4个字节就是存放虚表的地址，该地址指向了一张虚表，虚表也叫做虚函数表，因为虚表里面存放的是函数地址。上图就是一个cat对象在内存中的情况。

也就意味着，一旦多了虚函数，Cat对象就会多出4个字节，该4个字节是存放着一个地址值，并且该地址值是虚表的地址值，根据该地址值，就能找到这张虚表，然后利用虚表中存放的函数地址，调用对应的函数。

那现在可以从汇编层面来进行分析，将上面代码运行起来后，得到的汇编为

![1574081402095](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574081402095.png)

上图是在有虚函数时，调用speak函数的汇编指令。然后将指令进行剖析，得到下图

![1574081925133](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574081925133.png)

接下来在观察run函数是怎么调用的；同样将程序运行起来，得到run函数调用的汇编代码

![1574081859502](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574081859502.png)

run函数调用汇编指令剖析

![1574082249324](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574082249324.png)

现在已经从汇编层面，证明了在有虚函数时，调用函数时，确实有虚表的存在，并且确实是根据上表中内存示意图的方式，一步一步的调用函数的。接下来再从内存层面来证明虚表中存放的，确实是当前对象的函数地址。

现在将程序打上断点，并运行起来，可以得到堆空间中cat对象的地址值。

![1574082720956](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574082720956.png)

拷贝该地址值，然后再内存中搜索该地址值

![1574082932482](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574082932482.png)

从该地址值开始的12个字节，就是cat对象的内存，为了证明该内存确实是为cat对象的内存，现在将代码跳过一行，执行cat->m_age，然后得到内存图

![1574083167924](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574083167924.png)

![1574083188489](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574083188489.png)

看到内存中的值发生了变化，并且16进制的14对应10进制的20，说明该块内存空间是m_age的地址。

到这里已经得到了cat对象的地址，并且可以得到cat对象前4个字节中存储的内容，为68 9b ee 00，由于现在电脑是小端模式，最终的值为00ee9b68，则虚表的地址就位0x00ee9b68，然后再利用该地址，在内存中搜索，找到虚表的存储空间中存储的内容

![1574083588972](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574083588972.png)

利用搜索出来的地址，然后将前面8个字节转换为2个地址值。由于是小端模式，所以转换后的地址为0x00ee1460与0x00ee1028。现在将断点从的程序转到汇编代码，并单步调试至调用speak函数的地方，进入函数。可以得到该函数的地址值，得到下图

![1574084009888](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574084009888.png)

可以看到，现在汇编代码中的地址值为0x00ee1460与前面计算的地址值相等。所以虚表中前面的4个字节，是cat对象中speak函数的调用地址。现在将断点打在调用run函数的地方，再得到调用run函数的汇编指令。最终得到run函数的调用地址

![1574084295424](https://github.com/MSTGit/CPPNOTE/blob/master/VirtualTable/Resource/1574084295424.png)

可以发现，该地址同样与前面计算出来的地址值相等。所以虚表中的后面4个字节，是cat对象中run函数的调用地址。

通过上面的步骤，就证明了虚表的存在，并且虚表中存储的是对象的虚函数地址

#### 虚析构函数

如果存在父类指针指向子类对象的情况，应该将析构函数声明为虚构函数（虚析构函数）

为什么要这样呢？

假设现在上面的代码增加了析构函数

```C++
struct Animal {
	int m_age;
	void speak() {
		cout << "Animal::speak()" << endl;
	}

	void run() {
		cout << "Animal::run()" << endl;
	}

	Animal() {
		cout << "Animal::Animal()" << endl;
	}
	~Animal() {
		cout << "Animal::~Animal()" << endl;
	}
};

struct Cat : Animal {
	int m_life;
	void speak() {
		cout << "Cat::speak()" << endl;
	}

	void run() {
		cout << "Cat::run()" << endl;
	}

	Cat() {
		cout << "Cat::Cat()" << endl;
	}
	~Cat() {
		cout << "Cat::~Cat()" << endl;
	}
};
int main() {
	Animal* cat = new Cat();
	delete cat;
	getchar();
	return 0;
}
```

如果Animal中没有虚函数时，将程序运行起来，最终得到的结果为

```
Animal::Animal()
Cat::Cat()
Animal::~Animal()
```

发现了一个问题，在创建对象的时候，调用了Animal与Cat的构造函数，但是在析构时，却只调用了Animal的析构函数，Cat的析构函数没有调用。原因是这样的，现在没有虚函数，所以不存在虚表的概念，所以在析构的时候，只会根据指针的类型调用析构函数，在delete时cat为Animal类型，所以只会调用Animal的析构函数。

只有当将Animal的析构函数定义为虚函数时，在delete父类指针时，才会调用子类的析构函数，保证析构的完整性。

```
virtual ~Animal() {
    cout << "Animal::~Animal()" << endl;
}
```

#### 纯虚函数

纯虚函数：没有函数体且初始化为0的虚函数，用来定义接口规范

现有以下一段代码

```C++
struct Animal {
	virtual void speak() {
		cout << "Animal::speak()" << endl;
	}

	virtual void run() {
		cout << "Animal::run()" << endl;
	}
};

struct Pig : Animal{
	void speak() {
		cout << "Pig::speak()" << endl;
	}

	void run() {
		cout << "Pig::run()" << endl;
	}
};

struct Dog : Animal {
	void speak() {
		cout << "Dog::speak()" << endl;
	}

	void run() {
		cout << "Dog::run()" << endl;
	}
};

struct Cat : Animal {
	void speak() {
		cout << "Cat::speak()" << endl;
	}

	void run() {
		cout << "Cat::run()" << endl;
	}
};
```

子类都重写了父类中方法的实现，而且父类Animal自己实现的函数都有自己的实现，不过这种在某些情况下有一点不合理，Animal是一种比较抽象的概念，子类Cat，Dog，Pig才是比较具体的概念，这些类有具体的实现，是非常明确的。所以Animal类不应该有实现。

```C++
struct Animal {
	virtual void speak() = 0;

	virtual void run() = 0;
};
```

这种情况下，可以将不需要实现的函数，应该声明为纯虚函数。C++中的纯虚函数类似于Java中的抽象类/接口，类似于Objective-C中的协议

##### 抽象类

抽象类有以下特点

1. 含有纯虚函数的类，不可以实例化，不可以创建对象
   所以在上面定义的Animal类，是不可以创建对象的。

   ```
   Animal anim;//报错
   ```

2. 抽象类也可以包含非纯虚函数，成员变量

3. 如果父类是抽象类，子类没有完全重写纯虚函数，那么子类依然是抽象类

