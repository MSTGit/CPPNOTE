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