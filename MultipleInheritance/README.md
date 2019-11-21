#### 多继承

C++允许一个类可以有多个父类（不建议使用，会增加程序的复杂度）

关于C++ 的多继承，定义了以下几个类，Student，Worker，Undergraduate，这里可以看到，Undergraduate是继承了Student和Worker。这就是多继承

```C++
struct Student {
	int m_score;
	void study() {
		cout << "Student::study()" << m_score << endl;
	}
};

struct Worker {
	int m_salary;
	void work() {
		cout << "Worker::work()" << m_salary << endl;
	}
};

struct Undergraduate : Student ,Worker {
	int m_grade;
	void play() {
		cout << "Undergraduate::play()" << m_grade << endl;
	}
};
```

由于Undergraduate是同时继承了Student和Worker，所以Student和Worker的成员变量和函数，都会被继承下来。所以可以通过下面这种方式定义对象，访问成员变量和函数

```C++
Undergraduate ug;
ug.m_score = 100;
ug.m_salary = 2000;
ug.m_grade = 4;
ug.study();
ug.work();
ug.play();
```

看到这里，发现多继承与平时的单继承，其实也没多大区别，继承一个类，就是将父类的成员变量和方法直接拿过来。所以创建出一个ug对象，会占用12个字节的内存空间，分别是m_score，m_salary，m_grade，并且顺序为父类的成员变量在内存前面，当前类在内存后面，多个父类，先继承的成员变量靠内存的前面。其内存图如下

![1574250627709](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574250627709.png)

请注意，父类成员变量的顺序，只跟继承顺序有关，与其他因素无关。

#### 多继承体系下构造函数的调用

现在，将上面代码都增加对应的构造函数

```C++
struct Student {
	int m_score;
	Student(int score) :m_score(score) {}
	void study() {
		cout << "Student::study()" << m_score << endl;
	}
};

struct Worker {
	int m_salary;
	Worker(int salary) :m_salary(salary) {}
	void work() {
		cout << "Worker::work()" << m_salary << endl;
	}
};

struct Undergraduate : Student ,Worker {
	int m_grade;
	Undergraduate(int score , int salary ,int grade) :Student(score) , Worker(salary) ,m_grade(grade) {}
	void play() {
		cout << "Undergraduate::play()" << m_grade << endl;
	}
};
```

由于是多继承，因此在初始化当前子类对象是，需要初始化父类的成员变量，由于是多继承，因此需要在调用构造函数时，调用父类的构造函数，初始化父类。

#### 多继承-虚函数

如果子类继承的多个父类都有虚函数，那么子类对象就会产生对应的多张虚表。

```C++
class Student{
public:
	virtual void study() {
		cout << "Student::study()" << endl;
	}
};

class Worker {
public:
	virtual void work() {
		cout << "Worker::work()" << endl;
	}
};

class Undergraduate : Student, Worker {
	void play() {
		cout << "Undergraduate::play()" << endl;
	}

	void study() {
		cout << "Undergraduate::study()" << endl;
	}

	void work() {
		cout << "Undergraduate::work()" << endl;
	}
};
```

上面代码中，父类均有虚函数，因此创建子类对象ug，在子类对象中，就会对应生成多张虚表。

![1574251707487](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574251707487.png)

#### 同名函数

如果多个父类中都有一个相同的函数。例如下面的代码

```C++
class Student {
public:
	void eat() {
		cout << "Student::eat()" << endl;
	}
};

class Worker {
public:
	void eat() {
		cout << "Worker::eat()" << endl;
	}
};

class Undergraduate : public Student, public Worker {
public:
	void eat() {
		cout << "Undergraduate::eat()" << endl;
	}
};
```

在这种情况下，如果创建Undergraduate对象后，调用eat函数，如下代码。调用的肯定是子类中的eat。

```C++
int main() {
	Undergraduate ug;
	ug.eat();
	return 0;
}
```

但是如果想调用其中父类的eat的话，这需要加上作用域来进行调用。

```C++
int main() {
	Undergraduate ug;
	ug.eat();
	ug.Student::eat();
	ug.Worker::eat();
	return 0;
}
```

最终，就可以成功调用到对应父类中的函数了。

#### 同名成员变量

在多继承中，会出现一个很有意思的现象，多个父类中的成员变量可能重名。并且子类也可能会与子类中的成员变量重名。如下列情况

```C++
class Student {
public:
	int m_age;
};

class Worker {
public:
	int m_age;
};

class Undergraduate : public Student, public Worker {
public:
	int m_age;
};
```

这种代码，编译是不会报错的，在C++里面，允许成员变量重名。但是很多编程语言是不允许这样做的，例如Java，Objective-C，所以在上面这种情况下，如果创建出一个Undergraduate对象的话，也是占用12个字节的内存空间，会将Student的m_age继承下来，也会将Worker的m_age继承下来，最终就会有3个m_age，只不过访问的时候很有意思，与刚刚重名函数的访问方式一样。

```C++
int main() {
	Undergraduate ug;
	ug.m_age = 10;
	ug.Student::m_age = 20;
	ug.Worker::m_age = 30;
	getchar();
	return 0;
}
```

对应的内存结构图为

![1574253292402](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574253292402.png)

通过这张内存结构图，相信就可以一目了然的知道成员变量的布局了。

#### 菱形继承

由于C++多继承的支持，所以在开发中可能会出现菱形继承的情况。所谓的菱形继承，就是继承的体系像菱形一样。

![1574254075482](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574254075482.png)

对应到类中，这会出现这样的继承体系。

![1574254465105](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574254465105.png)

对应到代码当中，如下面这种情况

```C++
struct Person {
	int m_age;
};

struct Student : Person {
	int m_score;
};

struct Worker : Person {
	int m_salary;
};

struct Undergraduate : Student, Worker {
	int m_grade;
};
```

请问现在假设通过Undergraduate创建出一个对象，会占用多大的内存空间呢？从表面上看，子类继承自父类，会将父类的成员变量继承下来。所以Undergraduate继承自Student，会将Student的成员变量继承过来，继承自Worker，又会将Worker的成员变量继承过来，然后Student和Worker又继承自Person，又会将Person的成员变量继承过来，按照这种思路，Undergraduate应该有4个成员变量， 这样的话，应该是占用16个字节的存储空间。但是实际是多少呢？如果通过sizeof关键字来获取的话，得到的结果是20。

为什么是20呢？首先，Student继承自Person，所以会将Person的成员变量继承过来，所以Student现在有2个成员变量，Worker继承自Person，所以又会将Person的成员变量继承过来，所以Worker现在有2个成员变量，所以等价于下面这种情况

```C++
struct Student {
	int m_age;
	int m_score;
};

struct Worker {
	int m_age;
	int m_salary;
};
```

然后Undergraduate继承自Student，所以又等下与这种写法

```C++
struct Undergraduate : Worker {
	int m_age;
	int m_score;
	int m_grade;
};
```

最后Undergraduate又继承自Worker，所以最终等价于

```C++
struct Undergraduate {
	int m_age;
	int m_score;
	int m_age;
	int m_salary;
	int m_grade;
};
```

Undergraduate类中有5个int成员变量。所以会占用20个字节的存储空间。但是这种情况是又问题的，m_age这个成员变量最终是来自Person，所以m_age这个成员变量，只需要保留一份就可以了。基于这种问题的存在，所以菱形继承有以下问题。

1. 最底下子类从基类继承的成员变量冗余，重复
2. 最底下子类无法访问基类的成员，有二义性。

基于菱形继承访问基类成员的二义性，因此下面这种写法会报错

```c++
Undergraduate ug;
ug.m_age;
```

因为在这种情况下访问m_age，无法确定是访问Student父类中的m_age还是Worker父类中的m_age。针对这种问题，到底应该怎么解决呢？可以用虚继承的方式来解决

#### 虚继承

说到虚，可能会想到虚函数。现在又将了解一个新的概念，虚继承，虚继承可以解决菱形继承带来的问题。虚继承以后，最终导致的效果就是，上面的菱形继承会共用一个m_age成员变量，不会导致成员变量的冗余和重复。Person这个类，就成为虚基类

![1574255984047](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574255984047.png)

对应到代码则是下面这样

```C++
struct Person {
	int m_age;
};

struct Student : virtual Person {
	int m_score;
};

struct Worker :virtual Person {
	int m_salary;
};

struct Undergraduate : Student, Worker {
	int m_grade;
};
```

通过虚继承的方式，就可以解决访问基类中成员变量报错的问题。但是需要注意虚继承的位置，虚继承是为了解决基类中成员变量重复的问题。所以虚继承的位置应该是Person的子类虚继承Person

如果现在为类中的每一个成员变量都赋一个初始值，观察最终的内存图

```C++
struct Person {
	int m_age = 1;
};

struct Student : virtual Person {
	int m_score = 2;
};

struct Worker :virtual Person {
	int m_salary = 3;
};

struct Undergraduate : Student, Worker {
	int m_grade = 4;
};
```

需要注意，一旦虚继承的话， 在对象的内存里面，会多4个字节用来存放虚表的地址，与虚函数的方式一样。并且虚继承的成员变量，会放到内存地址的最后面，因此如果创建一个Student对象的话，对应的内存布局是这样的

![1574256773865](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574256773865.png)

然后虚表里面放着2个东西，第一个是虚表指针与本来起始地址的偏移量（一般是0），另外一个是虚基类第一个成员变量与本类起始地址的偏移量（这里就是m_age与本类起始地址的偏移量），所以Student对象虚表指针内存布局与Person对象关系如下

![1574257051702](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574257051702.png)

同理，Worker创建的对象，也是一样的

![1574257224302](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574257224302.png)

创建出一个Undergraduate对象的话，现在Undergraduate对象是同时继承自Student和Worker，如果按照正常的逻辑来讲，继承自Student，会将Student所有的成员变量放到最前面，然后接下来放Worker的成员变量，最后把自己的放最后面，这种做法是默认的做法。如果父类是虚继承的话，最终的话只会将Student父类中的虚表和Student父类中的成员变量放到内存地址的最前面，Worker也同理。接下来放的是自己的成员变量，最终才是虚基类中的成员变量。所以对应的内存布局是这样的。

![1574257676488](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574257676488.png)

对应的虚表中记录的偏移量为

![1574257888354](https://github.com/MSTGit/CPPNOTE/blob/master/MultipleInheritance/Resource/1574257888354.png)

但是通过虚继承的方式实现，发现了一个问题，最终Undergraduate对象占用的存储空间反而增大了。前面在没有使用虚继承时，占用的是20个字节的存储空间，现在占用了24个字节的存储空间。从表面看，好像并不划算。需要注意，现在这种情况只是在测试阶段，如果是在实际开发中，虚基类中一般会有多个成员变量，哪个时候就节省内存空间。

#### 多继承的价值

假设现在要实现这样一个功能

兼职中心，招聘保姆，岗位如下：

1. 保姆：扫地，做饭
2. 老师：踢足球，打棒球

应聘的角色如下：

1. 学生
2. 上班族

所以可以通过下面这种方式来定义两个角色，学生既可以当保姆，也可以当老师，上班族可以做老师，就可以使用下面方式来定义

```C++
class JobBaomu {
public:
	virtual void clean() = 0;
	virtual void cook() = 0;
};

class JobTeacher {
public:
	virtual void playFootball() = 0;
	virtual void playBaseball() = 0;
};

class Student : public JobBaomu, public JobTeacher{
	int m_score;
public:
	void clean() {}
	void cook() {}

	void playFootball() {}
	void playBaseball() {}
};

class Worker : public JobTeacher {
	int m_salary;
public:
	void playFootball() {}
	void playBaseball() {}
};
```

通过这种方式，可以定义规范标准，只要能实现对应的标准，就可以继承该类，然后实现逻辑。这种定义规范的方式，类似于Java中的接口，Objective-C中的协议。