#### 析构函数（Destructor）

> 析构函数（也叫析构器）,在对象销毁的时候自动调用，一般用于完成对象的清理工作

在前面，已经知道了，如果构造函数被调用，是新对象诞生的象征。与之相反的，如果对象的析构函数被调用，则是对象的内存即将被回收，对象即将被销毁的象征。

析构函数的特点：

函数名以~开头，与类同名，无返回值（void都不能写），无参，不可以重载，有且只有一个析构函数

```C++
struct Person {
	Person() {
			cout << "Person::Person()" << endl;
	}
	~Person() {
		cout << "~Person::Person()" << endl;
	}

};
```

我们在测试是，可以在main函数中这样进行调用

```C++
int main() {
	cout << 1 << endl;
	{
		Person person;
	}
	cout << 2 << endl;

	getchar();
	return 0;
}
```

通过改变person对象的作用域的话，就可以成功的看到，析构函数被调用了。并且调用的时机是在1与2之间。

注意：通过malloc分配的对象free的时候不会调用析构函数；即通过下面方式分配的对象，在free的时候，不会调用析构函数

```C++
int main() {
	Person* p = (Person*)malloc(sizeof(Person));
	free(p);

	getchar();
	return 0;
}
```

#### 析构函数的作用

前面，知道了析构函数是在对象即将被销毁时，做一些收尾的工作，但是假设类中定义了一些成员变量时，创建的对象被销毁时，一般不需要做任何操作，因为对象销毁时，对象所在的内存空间中，保存的成员变量，也将被回收，例如下列的情况

```C++
struct Person {
	int m_age;
	Person() {
		cout << "Person::Person()" << endl;
	}
	~Person() {
		cout << "~Person::Person()" << endl;
	}
};
```

上面这种情况，当创建的Person对象销毁时，Person对象中的m_age成员变量，也会自动被回收掉，那么析构函数到底有什么作用呢？

那请看下面这种情况，假设现在Person有一个属性m_car，表示创建出来的每一个Person对象，都有一辆车。

```C++
struct Car {
	int m_price;
	Car() {
		m_price = 0;
		cout << "Car::Car()" << endl;
	}
	~Car() {
		cout << "~Car::Car()" << endl;
	}
};

struct Person {
	int m_age;
	Car* m_car;
	Person() {
		m_age = 0;
		m_car = new Car();
		cout << "Person::Person()" << endl;
	}
	~Person() {
		cout << "~Person::Person()" << endl;
	}
};

int main() {
	{
		Person person;
	}
	getchar();
	return 0;
}
```

按照前面的结论，当创建出来的person对象销毁时，person对象中的成员变量也将要被销毁，但是当将这段程序运行起来以后，会发现一个问题，最终打印的结果为

```
Car::Car()
Person::Person()
~Person::Person()
```

Car对象中的析构函数没有调用，析构函数没有调用，则说明Car对象没有销毁，那么这段程序存在内存泄漏（内存泄漏：该释放的内存并没有得到释放）的问题，为什么Car对象没有释放呢？先来看看创建出来的对象，在内存中是如何分布的吧！

![1573892066714](https://github.com/MSTGit/CPPNOTE/blob/master/Destructor/Resource/1573892066714.png)

所以前面的Car对象是通过new出来的，在构造函数章节知道了，new出来的对象，申请的内存空间在堆空间，堆空间的内存不会自动回收，所以当person对象销毁的时候，内存布局是这样的，

![1573892543399](https://github.com/MSTGit/CPPNOTE/blob/master/Destructor/Resource/1573892543399.png)

所以person对象的自动回收，并不代表堆空间的car对象也会回收。因此需要主动通过delete方式来释放，那么可以在person对象即将被系统回收前，将对象拥有的car也释放掉，所以可以这样来修改

```C++
~Person() {
	delete m_car;
    cout << "~Person::Person()" << endl;
}
```

通过主动调用delete以后，最终car对象被成功释放

```
Car::Car()
Person::Person()
~Car::Car()
~Person::Person()
```

析构函数，用来做内存清理工作，清理内部产生的堆空间，例如上面的car对象，是在Person类中new出来的，所以在person对象销毁时，需要将类中new出来的对象也释放掉。

##### 析构函数内存管理分析

###### 情况一

为了充分认知对象的内存管理，再看看一下这几种情况，如果代码是这样的

```C++
struct Car {
	int m_price;
};

struct Person {
	int m_age;
	Car m_car;
};
int main() {
	{
		Person person;
	}
	getchar();
	return 0;
}
```

通过这种方式创建出来的person对象，car对象也在栈里面，内存分布如下，这种情况下的person对象占用8个直接的存储空间

![1573892925541](https://github.com/MSTGit/CPPNOTE/blob/master/Destructor/Resource/1573892925541.png)

###### 情况二

如果代码修改为这种情况呢？

```C++
struct Car {
	int m_price;
};

struct Person {
	int m_age;
	Car m_car;
};
int main() {
	{
		Person *p = new Person();
	}
	getchar();
	return 0;
}
```

通过这种凡是创建出来的对象，是指针变量p指向了堆空间的一块内存[下图]

![1573893122802](https://github.com/MSTGit/CPPNOTE/blob/master/Destructor/Resource/1573893122802.png)

###### 情况三

假设现在是代码是这种情况

```
struct Car {
	int m_price;
};

struct Person {
	int m_age;
	Car *m_car;
	Person() {
	 	m_car = new Car();
	}
	~Person() {
		delete m_car;
	}
};
int main() {
	{
		Person *p = new Person();
	}
	getchar();
	return 0;
}
```

这种情况，稍微复杂一些，不过根据前面的结论，也容易很快的想出来，其内存分布是怎么样的。

![1573893441220](https://github.com/MSTGit/CPPNOTE/blob/master/Destructor/Resource/1573893441220.png)

相信根据以上分析的几种情况，以后在写出一段代码，创建一个对象，你一定知道这一段代码，创建出来的对象，牵扯到了哪些内存区域，并且每个对象应该存放在哪个位置都是很清楚的了。所以一定要扫除一个误区：指针变量并不是都在栈空间，基本数据类型也不都是在栈空间。

一个变量的内存在哪个区域，取决于内存的申请方式