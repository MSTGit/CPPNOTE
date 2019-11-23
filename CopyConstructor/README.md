#### 拷贝构造函数（Copy Constructor）

拷贝构造函数，也是构造函数的一种。大家都知道，构造函数是在对象创建时调用。当利用已存在的对象，创建一个新对象时（类似于拷贝），就会调用新对象的拷贝构造函数进行初始化，所以同下面方式创建的car2对象，就会调用拷贝构造函数

```C++
class Car {
	int m_price;
	int m_length;
public:
	Car(int price = 0, int length = 0) :m_price(price), m_length(length) {
		cout << "Car(int price = 0, int lenght = 0)" << endl;
	}

	void display() {
		cout << "price=" << m_price << ", length=" << m_length << endl;
	}
};

int main() {
	Car car1;
	Car car2(car1);
	getchar();
	return 0;
}
```

上面就是利用已经存在的car1对象，创建一个新的car2对象，car2的初始化，就会调用拷贝构造函数。也就是说，car2的诞生，不会调用普通的构造函数。如果现在将程序运行起来，则只会看到调用了一次构造函数，既然新对象创建出来，都会调用构造函数，说明car2调用的是拷贝构造函数。拷贝构造函数是通过这种格式来进行定义的

```C++
Car(const Car& car) {
    cout << "Car(const Car& car)" << endl;
}
```

如果现在将拷贝构造函数定义在上面的类中，再次运行程序，则会发现，拷贝构造函数是有调用的。并且如果通过有初始化的对象来进行拷贝新的对象，新的对象访问成员变量时的值与原对象的值一样。即下面这段代码，打印出来的结果是相同的。

```C++
int main() {
	Car car1(100,5);
	Car car2(car1);
	car1.display();
	car2.display();
	getchar();
	return 0;
}
```

首先来看看，如果现在不自己定义拷贝构造函数时，它的底层调用是怎么样的

![1574476160962](https://github.com/MSTGit/CPPNOTE/blob/master/CopyConstructor/Resource/1574476160962.png)

通过汇编代码可以看见，首先是利用一个地址值取出前4个字节，然后赋值到一个新的存储空间，紧接着有将另外一个地址值中4个字节的内容取出来，又放到一个新的存储空间。所以可以发现，一共是取出了8个字节的内容，然后放到了另外一个存储空间。并且仔细看取的源地址会发现，两个地址是连续的，即edb-10h的地址与edp-0ch的地址是连续的，因为我们可以知道，这两个地址值相差的值是4；而且看到两次存放的目的地址，edp-20h与edp-1ch的地址值也是连续的。所以拷贝操作有点类似于下面这种操作

```C++
Car car1(100,5);
Car car2;
car2.m_price = car1.m_price;
car2.m_length = car2.m_length;
```

这种操作对应的汇编代码为

![1574476796849](https://github.com/MSTGit/CPPNOTE/blob/master/CopyConstructor/Resource/1574476796849.png)

可以发现，汇编代码的层面来看，这两段汇编代码是一样的，所以拷贝对象成员成员变量的值来源等价于这种方式。

需要注意，如果自己自定义了拷贝构造函数的实现，则需要在拷贝构造函数内部，自己实现成员变量拷贝操作。所以在这里的自定义拷贝构造函数，需要这样实现

```C++
Car(const Car& car) {
    m_price = car.m_price;
    m_length = car.m_length;
}
```

总结：

构造函数是对象创建时，就会调用。拷贝构造函数是利用一个对象，创建出一个新对象时调用。

###### 调用父类的拷贝构造函数

在前面，普通情况下，存在继承关系，需要初始化父类的成员变量时，需要在子类构造函数中调用父类的构造函数

```C++
class Person {
	int m_age;
public :
	Person(int age = 0) :m_age(age) {}

};

class Student : public Person {
	int m_score;
public:
	Student(int age = 0, int score = 0) : Person(age), m_score(score) {}
};
```

拷贝构造函数，也是一样的。可以通过子类的拷贝构造函数调用父类的拷贝构造函数

```C++
class Person {
	int m_age;
public :
	Person(int age = 0) :m_age(age) {}
	Person(const Person& person) :m_age(person.m_age) {}
};

class Student : public Person {
	int m_score;
public:
	Student(int age = 0, int score = 0) : Person(age), m_score(score) {}
	Student(const Student& student) :Person(student), m_score(student.m_score) {}
};
```

同样需要注意，如果没有自己实现拷贝构造函数的话，也同样可以完成拷贝操作。

