我们都知道，面向对象有三大特性，封装，继承，多态。前面章节分别对封装和继承进行了说明，封装就是成员变量私有化，然后提供公共的get和set方法，去访问成员变量；继承可以让之类拥有父类的所有成员。在本章节中，将聊一聊关于多态的一些知识点。

#### 父类指针、子类指针

在面向对象开发中，父类指针可以指向子类对象，是安全的，开发中也经常用到。例如下列的这种写法，就是使用父类指针指向子类对象

```C++
struct Person {
	int m_age;
};

struct Student : Person {
	int m_score;
};

int main() {
	Person* p = new Student;
	getchar();
	return 0;
}
```

但是，在默认情况下， 子类指针是不允许指向父类对象的，因为这种行为是不安全的。即下列的这种写法是不允许

```C++
Student* p = new Person;
```

首先，来想一想，为什么允许父类指针指向子类对象？从编译器的角度来讲，下面这句代码对应下图对应，相信你是可以明白的

```C++
Person* p = new Student;
```

![1573995180911](https://github.com/MSTGit/CPPNOTE/blob/master/Polymorphism/Resource/1573995180911.png)

但是虽然现在创建的对象是一个Student对象，但是是用Person指针指向该对象的，所以*p指针可以访问的成员变量就只有m_age，所以这样做是安全的。但是如果反过来，那代码就可以这样写

```C++
Student* p = (Student *)new Person;
p->m_age = 10;
p->m_score = 100;
```

对应指针与对象的关系如下图

![1573995878961](https://github.com/MSTGit/CPPNOTE/blob/master/Polymorphism/Resource/1573995878961.png)

可以看到*p指向的是Person对象，但是写代码是，却可以访问m_age和m_height，由于当前的情况下，创建一个Person对象只占用4个字节，但是这个时候，编译器认为 *p指向的是一个Student对象，所以在使用 *p访问成员变量时，可以访问Student对象内存大小的区域，即8个字节的内存空间，很明显已经超出了Person对象的内存区域。所以这种方式是不安全的。

#### 多态

在前面，已经知道了，父类指针可以指向子类对象，接下来，来聊一聊多态

现在定义了多种动物的类

```C++
struct Pig {
	void speak() {
		cout << "Pig::speak()" << endl;
	}

	void run() {
		cout << "Pig::run()" << endl;
	}
};

struct Dog {
	void speak() {
		cout << "Dog::speak()" << endl;
	}

	void run() {
		cout << "Dog::run()" << endl;
	}
};

struct Cat {
	void speak() {
		cout << "Cat::speak()" << endl;
	}

	void run() {
		cout << "Cat::run()" << endl;
	}
};
```

假设现在有一个遛狗的需求，可能这样来实现

```C++
void liu(Dog* p) {
	p->speak();
	p->run();
}
int main() {

	liu(new Dog());
	getchar();
	return 0;
}
```

如果将程序运行起来，相信是没有问题的，Dog会执行speak函数与run函数，但是有一个问题，现在如果你要溜猫，要溜猪的话。就需要分别重载liu函数，然后分别传入对象指针

```C++
void liu(Dog* p) {
	p->speak();
	p->run();
}

void liu(Cat* p) {
	p->speak();
	p->run();
}

void liu(Pig* p) {
	p->speak();
	p->run();
}
```

但是这种写法有问题，扩展性很差，如果后面有新的动物，需要对每一个动物类都写一遍liu函数。这样太麻烦了

，所以为了解决这个问题，可以将所有的动物都继承自Animal类

```C++
struct Animal {
	void speak() {
		cout << "Animal::speak()" << endl;
	}

	void run() {
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

根据前面说的，父类指针可以指向子类对象，所以liu方法可以这样来修改

```C++
void liu(Animal* p) {
	p->speak();
	p->run();
}
```

这样的话，就可以父类指针指向子类对象，来调用子类对应函数的实现。并且希望达到的结果为liu函数里面，传入的是Dog就调用dog对应speak，run的实现，传入的Cat，就调用cat对应speak，run的实现。现在可以将程序运行起来看最终的结果，发现最后并没有达到所期望的结果，传入的对象为子类时，调用的却还是父类的实现，说明并没有实现多态。原因是在默认情况下，编译器只会根据指针类型调用对应的函数，不存在多态。那接下来通过汇编代码，看一下究竟是什么原因吧！

如果现在代码是这样写的

```C++
Animal* p = new Dog();
p->run();
p->speak();
```

代码转为的汇编代码

![1573999513913](https://github.com/MSTGit/CPPNOTE/blob/master/Polymorphism/Resource/1573999513913.png)

在汇编代码里面可以看到，call函数调用的是一个固定的函数地址，说明不管当前*p指针指向的什么对象，最终都会调用该函数。所以说明具体应该调用哪个函数，在代码编译阶段就已经确定了，不会根据对象去找对应对象方法的实现。

在C++里面，如果想要实现多态，需要通过虚函数来实现。

#### 虚函数

虚函数：被virtual修饰的成员函数，成为虚函数

所以，现在将Animal类中的两个函数，变为虚函数的话，就可以实现多态了，即Animal类修改为

```C++
struct Animal {
	virtual void speak() {
		cout << "Animal::speak()" << endl;
	}

	virtual void run() {
		cout << "Animal::run()" << endl;
	}
};
```

将程序运行起来以后，可以看到，调用了对象真正函数的实现。然后对应的汇编代码可以发现，发生了改变

![1574000427730](https://github.com/MSTGit/CPPNOTE/blob/master/Polymorphism/Resource/1574000427730.png)

现在call调用的是寄存器中存储的内容，所以寄存器里面可以存不同的地址，最终调用的是根据寄存器内容，来决定调用哪个函数，是动态的

#### 多态总结

多态是面向对象非常重要的一个特性

1. 同一操作作用于不同的对象，可以有不同的解释，产生不同的执行结果
2. 在运行时，可以识别出真正的对象类型，调用对应子类中的函数

多态的要素

1. 子类重写父类的成员函数（override）
2. 父类指针指向子类对象
3. 利用父类指针调用重写的成员函数