#### 初始化列表

在以前，初始化成员变量是通过这种方式来进行的

```C++
struct Person {
	int m_age;
	int m_height;

	Person(int age, int height) {
		m_age = age;
		m_height = height;
	}
};
int main() {

	Person person(18, 180);
	getchar();
	return 0;
}
```

通过定义一个构造函数，然后再创建对象时，调用对应的构造函数时传入参数，在构造函数内部对成员变量进行初始化。初始化可以更便捷的方式来对成员变量进行初始化，初始化列表有以下特点：

> 1. 一种便捷的初始化成员了变量的方式
> 2. 只能用在构造函数中
> 3. 初始化顺序只跟成员了变量的声明顺序有关

初始化列表的格式如下：

```C++
struct Person {
	int m_age;
	int m_height;
	Person(int age, int height) :m_age(age), m_height(height) {
	}
};

int main() {

	Person person(18, 180);
	cout << person.m_age << endl;
	cout << person.m_height << endl;
	getchar();
	return 0;
}
```

通过初始化列表的方式初始化成员变量与在构造函数中的方式初始化成员是等价的。并且通过程序运行的结果，也确实能达到与构造函数中初始化成员变量的目的。

##### 证明初始化列表与普通初始化方式等价

如果将本文中第一段代码运行起来，然后看生成的汇编代码

![1573975358922](https://github.com/MSTGit/CPPNOTE/blob/master/InitializationList/Resource/1573975358922.png)

通过生成的汇编代码，明显看到，分别有对m_age与m_height赋值。

然后，再将初始化列表初始化成员变量的方式运行起来，然后看生成的汇编代码

![1573975627272](https://github.com/MSTGit/CPPNOTE/blob/master/InitializationList/Resource/1573975627272.png)

同样的，在这一段汇编代码中，同样看到了有对m_age与m_height赋值，并且生成的汇编指令是一样的。所以两种写法是完全等价的。对于初始化列表的这种方式，可以理解为是一种语法糖。

##### 初始化列表中成员变量的初始化顺序

如果现在将初始化列表进行一些调整

```C++
struct Person {
	int m_age;
	int m_height;
	Person(int age, int height) :m_age(m_height), m_height(height) {
	}
};

int main() {

	Person person(18, 180);
	cout << person.m_age << endl;
	cout << person.m_height << endl;
	getchar();
	return 0;
}
```

最终打印出来的结果m_age是一堆乱七八糟的值，说明m_age并没有初始化，而且，如果将初始化列表中的m_age,m_height赋值顺序进行调换，也会出现一样的情况，说明在通过初始化列表初始化成员变量时，与初始化列表的赋值顺序无关。如果将成员变量的定义顺序调换以下， 最终得到的结果是两个成员变量都得到了初始化，所以需要注意**初始化列表成员变量初始化顺序只与成员变量的定义顺序有关**

#### 默认参数与初始化列表的配合使用

利用前面的默认参数，与初始化列表结合的话，会起到什么样的效果呢？

```C++
struct Person {
	int m_age;
	int m_height;
	Person(int age = 0, int height = 0) :m_age(age), m_height(height) {
	}
};

int main() {

	Person person1;
    Person person2(17);
    Person person3(17,170);
	getchar();
	return 0;
}
```

通过默认参数，就可以选择在初始化的时候，是否设置成员变量的初始值，初始化对象时，更加方便。

#### 构造函数的相互调用

有时候在编写程序时，有一种需求，在初始化对象时，需要将所有变量都初始化，但是有提供了多个构造函数，如果在每个构造函数都将成员变量单独初始化一遍的话，就会导致很多重复的代码，在这种情况下，就会考虑使用构造函数来调用其他构造函数初始化成员变量。

```C++
struct Person {
	int m_age;
	int m_height;
	Person(){
	
	}
	Person(int age, int height) {
		m_age = age;
		m_height = height;
	}
};

int main() {
	Person person;
	cout << person.m_age << endl;
	cout << person.m_height << endl;
	getchar();
	return 0;
}
```

如果现在想要调用无参的构造函数，并且最终创建出来对象的成员变量，都有初始值的话，你可能会想到在无参的构造函数里面调用有参的构造函数，即将代码修改为这样

```C++
Person(){
	Person(10,180);
}
```

如果这样调用的话，你会发现最终在获取创建出来对象的成员变量时，得到的值同样是乱七八糟的，说明通过这种方式成员变量并没有得到初始化。在构造函数章节里面讲到，构造函数被调用，就标志着一个新的对象被创建，说明这种方式是在无参构造函数里面创建了一个新的对象，并且在无参构造函数调用完毕后，就销毁了，对象的销毁，也可以通过析构函数得到证明。那应该怎样初始化呢？根据C++语法的要求，在构造函数相互调用时，只能构造函数放到初始化列表当中，所以需要修改为下面这种形式

```C++
Person() :Person(10,180){
}
```

将构造函数进行修改以后，最终可以看到，成功的通过构造函数调用了另外一个构造函数，并且成员变量也得到了初始化。

#### 父类的构造函数

假设现在有两个类，存在继承关系

```C++
struct Person {
	int m_age;
	Person(){
		cout << "Person::Person()" << endl;
	}
	
	Person(int age){
		cout << "Person::Person()" << endl;
	}
};

struct Student :Person {
	int m_no;
	Student() {
		cout << "Student::Student()" << endl;
	}
};

int main() {
	Student student;
	getchar();
	return 0;
}
```

在创建子类兑现时，构造函数是如何调用的呢？将程序运行起来以后，看到的结果是先调用父类的构造函数，然后再调用当前类的构造函数。并且在**默认情况下，会调用父类无参的构造函数**，但是，如果子类的构造函数显式地调用了父类的有参构造函数，则就不会再去默认调用父类的无参构造函数。可以通过初始化列表的方式来调用父类其他构造函数

```C++
Student() :Person(10) {
    cout << "Student::Student()" << endl;
}
```

关于这些结论，都可以在程序运行起来时，通过汇编代码来查看。

如果父类没有无参的构造函数，则需要在子类显式的调用父类有参的构造函数，但是如果父类没有构造函数，则子类不用调用父类的构造函数。