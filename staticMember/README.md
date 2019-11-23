#### 静态成员（static）

静态成员：被static修饰的成员变量/函数，可以称为静态成员。

可以通过对象（对象.静态成员）,对象指针（对象指针->静态成员），类访问（类名::静态成员）

现假设定义了以下一个类，分别定义了一个成员变量，一个成员函数，分别使用static来修饰该成员变量和成员函数

```C++
class Car {
public:
	int m_price;
	void run() {
		cout << "run()" << endl;
	}
};
```

如果使用Car分别创建不同的对象，然后对不同的成员变量赋值的话，最终保存起来的值是属于对应对象的，会保存在不同的内存区域，例如

```C++
Car car1;
car1.m_price = 100;

Car car2;
car2.m_price = 200;
```

分别访问car1和car2的m_price的话，会得到对应的值。

##### 静态成员变量

如果使用static来修饰成员变量，则成为静态成员变量，有以下特性

- 存储在数据段（全局区，类似于全局变量），整个程序运行过程中只有一份内存
- 对比全局变量，它可以设定访问权限（public，protected，private），达到局部共享的目的
- 必须初始化，必须在内外面初始化，初始化时，不能带static，如果类的声明和实现分离，在实现中初始化

所以将上面代码加上static后，并且在类外面对m_price进行初始化

```C++
class Car {
public:
	static int m_price;
	void run() {
		cout << "run()" << endl;
	}
};
int Car::m_price = 0;
```

可以通过以下方法来访问

```C++
Car car1;
car1.m_price = 100;

Car car2;
car2.m_price = 200;

Car::m_price = 300;

Car* p = new Car();
p->m_price = 400;
delete p;
```

并且需要注意，这里访问的m_price内存是同一块内存。

##### 静态成员函数

使用static来修饰的成员函数，可以成为静态成员函数，有以下特性

- 内部不能使用this指针（this指针只能用在非静态成员函数内部）
- 不能是虚函数（虚函数只能是非静态成员函数）
- 内部不能访问非静态成员变量/函数，只能访问静态成员变量/函数
- 非静态成员函数内部可以访问静态成员变量/函数
- 构造函数，析构函数不能是静态成员函数
- 当声明和实现分离时，实现部分不能带static

所以如果把上面的函数变为静态成员函数后

```C++
class Car {
public:
	static int m_price;
	static void run() {
		cout << "run()" << endl;
	}
};
int Car::m_price = 0;
```

可以通过下面这些方式来进行访问

```C++
Car car;
car.run();

Car* p = &car;
car.run();

Car::run();
```

所以，通过总结，如果是静态成员，都有三种访问方式，通过对象访问，通过指针访问，通过类名访问。

##### 静态成员变量汇编窥探

现在将上面的类进行稍微的修改

```C++
class Car {
public:
	int m_age;
	static int m_price;
	static void run() {
		cout << "run()" << endl;
	}
};
int Car::m_price = 0;
int main() {
	Car car;
	car.m_age = 1;
	car.m_price = 2;
	getchar();
	return 0;
}
```

现在将程序运行起来，得到以下的汇编代码

![1574344380236](https://github.com/MSTGit/CPPNOTE/blob/master/staticMember/Resource/1574344380236.png)

从汇编代码可以看到，首先是将1赋值到栈空间的一块地址，因为ebp是栈空间的一块地址值；接下来将2直接赋值到一块内存地址，并且是一块已经确定的地址值，而且看到，地址值前面有ds关键字，表示当前地址值是在数据段（date segment）,而且如果现在定义一个全局变量，会发现生成的汇编代码格式是一样的

```C++
class Car {
public:
	int m_age;
	static int m_price;
	static void run() {
		cout << "run()" << endl;
	}
};
int Car::m_price = 0;
int g_age;
int main() {
	Car car;
	car.m_age = 1;
	car.m_price = 2;
	g_age = 3;

	getchar();
	return 0;
}
```

最终生成的汇编代码是

![1574344817701](https://github.com/MSTGit/CPPNOTE/blob/master/staticMember/Resource/1574344817701.png)

从汇编代码可以看出，类里面定义的静态成员变量与类外面定义的全局变量，存放的区域是都是在同一块区域。

#### static应用场景-单例模式

单例模式：设计模式的一种，保证某个类永远只创建一个对象

在平时开发中，都知道，只要调用了一次构造函数，就会创建从一个对象。所以，在单例模式时，就要保证外面不能随便构造函数去创建对象。操作方法很简单，只需要将构造方法设计为私有的，就可以保证外界无法调用构造函数，但是又有一个问题，私有化构造函数后，外界不能创建对象，单例模式并不是一个对象都不能创建，且只能创建一个对象，并且整个程序运行中，只有一个对象，所以可以这样做，来获得一个单例对象

```C++
class Rocket {

private :
	Rocket() {};
    static Rocket* g_rocket;
public:
	static Rocket* sharedRocket() {
		if (g_rocket == NULL) {
			g_rocket = new Rocket();
		}
		return g_rocket;
	}

};
Rocket* Rocket::g_rocket = NULL;
int main() {
	Rocket* p1 = Rocket::sharedRocket();
	Rocket* p2 = Rocket::sharedRocket();
	Rocket* p3 = Rocket::sharedRocket();
	Rocket* p4 = Rocket::sharedRocket();
	Rocket* p5 = Rocket::sharedRocket();
	cout << p1 <<endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << p4 << endl;
	cout << p5 << endl;
	getchar();
	return 0;
}
```

最终程序运行起来后，得到的地址是一样的。这就证明了，这4次调用sharedRocket返回的都是同一个对象。

所以定义单例对象的步骤为

1. 构造函数私有化
2. 定义一个私有的static成员变量，指向唯一的哪个对象
3. 提供一个公共的访问但你对象的接口

不过这里，还需要考虑多线程访问造成的资源抢夺问题。