#### 继承

继承，可以让之类拥有父类的所有成员（变量/函数）

假设现在定义了如下两个类，一个是Student，一个是Worker，没个类中有自己的成员变量与函数。

```C++
struct Student {
	int m_age;
	int m_score;
	void run() {
	}
	void study() {
	}
};

struct Worker {
	int m_age;
	int m_salary;
	void run() {
	}
	void work() {
	}
};
```

现在很明显发现一个特点，这两个类是有一些共性的，大家都有m_age这个成员变量，大家都会跑步，但是也有一些个性化的东西，Student有自己的m_score，需要学习，Worker有自己的m_salary，需要工作，像这些共性的东西，一般来讲，都会抽到一个新的类中，将原有类中，个性化的东西留下，让后让原来的类，继承自新创建的类。通过继承建立类父子关系，这样子类就可以访问到父类中公共的成员变量与函数了。所以上面的代码，调整后为

```C++
struct Person {
	int m_age;
	void run() {
	}
};

struct Student : Person {
	int m_score;
	void study() {
	}
};

struct Worker : Person {
	int m_salary;
	void work() {
	}
};
```

所以看出，继承有一个很明显的好处就是代码可以重用，把公共的东西都统一放到一个类里面，然后其他类统一继承自该类，这就是继承的一个好处。所以最终如果创建一个Student对象的话，可以直接访问m_age的成员变量，也可以访问run()函数。

```C++
Student student;
student.m_age = 20;
student.m_score = 100;
student.run();
student.study();
```

Person与Student的关系描述

- Student是子类（subclass，派生类）
- Person是父类（superclass，超类）

#### 对象的内存布局

如果现在定义了如下的三个类，并且为依次继承的关系

```C++
struct Person {
	int m_age;
};

struct Student : Person {
	int m_no;
};

struct GoodStudent : Student {
	int m_money;
};
```

现在利用以上的几个类，创建出对应的对象，你知道这些对象在内存中分别占用多少个字节吗？相信你肯定知道，一个Person对象占用4个字节，一个Student对象占用8个字节，一个GoodStudent对象占用12个字节。

就拿GoodStudent创建的gs对象来说，假设m_age赋值为20，m_no赋值为1，m_money赋值为666，这12个字节在内存中是如何排布的呢？哪个成员变量排前面，哪个成员变量排后面呢？直接公布答案吧，这个直接打印成员变量地址就可以得出来，下图就是一个gs对象的内存布局

![1573905055479](https://github.com/MSTGit/CPPNOTE/blob/master/Inherit/Resource/1573905055479.png)

并且，从图中可以看出，每个成员变量占用4个字节的内存空间，而且也可以得出一个结论，从父类继承的成员变量会排在对象内存空间的前面，子类的成员变量在内存空间的后面。知道了GoodStudent创建出的对象的内存布局后，Student类创建出来的对象，肯定也就清楚了。