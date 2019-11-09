#### 类与对象

回想一下，面向对象有哪些常见知识点

1. 类
2. 对象
3. 成员变量，成员函数
4. 封装，继承，多态
5. ......

#### 类

在C++中，可以使用struct，class来定义一个类。是的，你没有看错，在C++中，可以用struct来定义一个类，在C语言里面，struct是结构体，但是在C++里面，可以直接将它理解为用来定义一个类的，struct与class都可以用来定义一个类。

所以，如果要定义一个Person类，就可以有以下两种方式来定义：

```C++
class Person{
	//成员变量
	int m_age;
	//成员函数
	void run() {
		cout << "Person :: run() - " << m_age <<  endl;
	}
};

struct Person{
	//成员变量
	int m_age;
	//成员函数
	void run() {
		cout << "Person :: run() - " << m_age <<  endl;
	}
};
```

发现了吗？C++中的结构体相比于C语言的结构体，多了可以在里面定义函数的功能，C语言中，结构体是只能定义成员变量的。

可以先利用结构体来创建一个对象，在C++里面创建对象非常简单

```C++
int main() {
    //利用结构体/类创建对象
	Person person;
	//访问person对象的成员变量
	person.m_age = 20;
	//用person对象调用成员函数
	person.run();

	//通过指针间接访问person对象
	Person* p = &person;
	p->m_age = 30;
	p->run();
	getchar();
	return 0;
}
```

上面代码中person对象，p指针的内存都是在函数的栈空间，系统自动分配和回收内存空间。

那么C++里面struct与class有什么区别呢？

> struct 与class的区别
>
> - struct的默认成员权限是public
> - class的默认成员权限是private

所以可以通过struct与class创建出来的对象，根据编译器的结果进行比较

struct创建的对象

```C++
struct Person{
	//成员变量
	int m_age;
	//成员函数
	void run() {
		cout << "Person :: run() - " << m_age <<  endl;
	}
};
int main() {
	Person person;
	person.m_age = 18;
	person.run();

	getchar();
	return 0;
}
```

编译器没有报错

![1573218826155](https://github.com/MSTGit/CPPNOTE/blob/master/ClassAndObject/Resource/1573218826155.png)

如果将struct换为class

```
class Person{
	//成员变量
	int m_age;
	//成员函数
	void run() {
		cout << "Person :: run() - " << m_age <<  endl;
	}
};
int main() {
	Person person;
	person.m_age = 18;
	person.run();

	getchar();
	return 0;
}
```

编译器报错了，并提示成员函数不可访问

![1573218941272](https://github.com/MSTGit/CPPNOTE/blob/master/ClassAndObject/Resource/1573218941272.png)

如果将class中的成员变量，成员函数访问权限修改为public，则不会报错

![1573219071924](https://github.com/MSTGit/CPPNOTE/blob/master/ClassAndObject/Resource/1573219071924.png)

所以，class的默认成员权限是private，struct的默认成员权限是public。

另外，也可以尝试反汇编，看一看struct与class是否有其他区别。所以可以通过class与struct来定义一个类，看以下最终生成的汇编代码。

利用struct定义的一个类

```C++
struct Car {
	int m_price;
};
int main() {
	Car car;
	car.m_price = 10;

	getchar();
	return 0;
}
```

对应生成的汇编代码

![1573221771916](https://github.com/MSTGit/CPPNOTE/blob/master/ClassAndObject/Resource/1573221771916.png)

最终看到，创建一个car对象，并为car对象的成员变量赋初始值的整个过程，只生成了一句汇编代码，并且是将0Ah放到了car对象的内存空间。因为当前的car对象只有一个int类型的成员变量，所以当前对象只占用4个字节的内存空间，所以现在car对象的地址值就是age变量的地址值。

现在利用class定义一个类

```C++
class Car {
public:
	int m_price;
};
int main() {
	Car car;
	car.m_price = 10;

	getchar();
	return 0;
}
```

然后再看以下对应生成的汇编代码

![1573222157851](https://github.com/MSTGit/CPPNOTE/blob/master/ClassAndObject/Resource/1573222157851.png)

是的，你没有看错，通过class与struct两种方式，生成的汇编代码是一样一样的

**注意：在实际开发中，用class表示类比较多**



#### C++编程规范

每个人都有自己的编程规范，没有统一的标准，没有标准答案，没有最好的编程规范，下面的参考仅供建议：

> 变量名规范参考
>
> - 全局变量：g_ 例如 int g_age = 10
>
> - 成员变量：m_ 例如 int m_age = 10
>
> - 静态变量：s_ 例如 static int s_age = 10
>
> - 常量：c_ 例如 const int c_int = 10
>
>   也可以使用驼峰标识 ，例如 g_age -> gAge

#### 对象的内存布局

在前面定义的一个person对象，在内存中占用多少个字节呢？答案是占用4个字节的内存空间，因为一个person对象，只有一个int类型的成员变量，因此每个对象，只需要保存自己对象的成员变量就可以了。比如下面的几个对象，都同样是每个对象分别占用4个字节的内存空间

```c++
int main() {
	Person person1;
	person1.m_age = 10;

	Person person2;
	person2.m_age = 20;

	Person person3;
	person3.m_age = 30;
	getchar();
	return 0;
}
```

##### 对象中函数内存问题

🤔前面说一个Person类创建出来的对象只占用4个字节的内存空间，难道类里面的函数，不占用内存吗？

如上面代码所示，分别定义了三个对象，并且大家都知道，三个对象都能调用对应的run函数，而且如果调用对象的run函数时，可以获得该对象成员变量的值m_age，那么是不是以为这这个对象里面是不是既有该成员变量，也有该函数呢?
是这样的，首先要想清楚一个问题。成员变量肯定是每个对象都有自己的成员变量，一定不能共用，因为person1的m_age是属于person1对象的，person2的m_age是属于person2的。每个对象的成员变量是对象特有的，所以每创建出来一个对象，都有自己的成员变量，都会为该对象的成员了变量分配内存。但是函数不需要每个对象都保存一份，因为函数是代码，每一个对象去调用同样一个函数的时候，调用的都是同一块代码，所以在保存函数时，就只会在内存中保留一份。如果后面对象需要调用该函数时，只需要通过函数的内存地址就可以找到对应的函数，然后调用该函数了，所有的对象共用一个函数。所以我们在前面的时候看到过call [地址]这种汇编，就是在调用函数，而且如果[]里面的地址相同的话，说明调用的是同一个函数。所以下面代码中run函数的地址都是一样的

```c++
int main() {
	Person person1;
	person1.m_age = 10;

	Person person2;
	person2.m_age = 20;

	Person person3;
	person3.m_age = 30;
	getchar();
	return 0;
}
```

![1573223816859](https://github.com/MSTGit/CPPNOTE/blob/master/ClassAndObject/Resource/1573223816859.png)

认真观察，最终调用的函数地址是同一个。

##### 对象的内存

🤔如果类中有多个成员变量，对象的内存有是如何布局的？

```C++
struct Person {
	int m_id;
	int m_age;
	int m_height;
	void display() {
		cout << "m_id is" << m_id << endl;
		cout << "m_age is" << m_age << endl;
		cout << "m_height is" << m_height << endl;
	}
};
```

请问现在如果创建一个Person对象，需要占用多少个字节？如果我们使用sizeof关键字来获取当前类创建对象后所占用的内存空间，得到的结果是12字节。那我们可以想象以下，当前Person有3个int类型的成员变量，并且创建出来的对象占用12字节的内存空间，最终该对象在内存中是怎么进行布局的。

该对象的成员变量是连续排布的，因为该对象占用12字节的存储空间，拥有3个int类型的成员变量，每一个int类型占用4个字节的存储空间，所以占用的12字节存储空间是用来存放int成员变量的。所以假设我们创建了一个如下的person对象

```C++
Person person;
person.m_id = 1;
person.m_age = 2;
person.m_height = 3;
```

最终，该person对象在内存中是这样布局的

![1573264580200](https://github.com/MSTGit/CPPNOTE/blob/master/ClassAndObject/Resource/1573264580200.png)

并且，成员变量在内存中的排列顺序是按照定义顺序来进行排列的。而且我们可以看到，0x00E69B60这个地址值，是m_id的地址值，并且也是person对象的地址值。并且，我们也可以通过打印，来获取当前创建出来对象和成员变量的地址值

```C++
cout << "&person == " << &person << endl;
cout << "&perosn.m_id == " << &person.m_id << endl;
cout << "&perosn.m_age == " << &person.m_age << endl;
cout << "&perosn.m_height == " << &person.m_height << endl;
```

最终打印的结果为

```
&person == 00AFF96C
&perosn.m_id == 00AFF96C
&perosn.m_age == 00AFF970
&perosn.m_height == 00AFF974
```

可以看到，person对象的地址值与m_id的地址值相等；m_id的地址值跳过4个字节，就是m_age的地址值，m_age的地址值跳过4个直接，就是m_height的地址值。

而且，也可以通过断点调试的方式类进行证明：

首先，我们在第二句打印的地方，添加一个断点

![1573265299235](https://github.com/MSTGit/CPPNOTE/blob/master/ClassAndObject/Resource/1573265299235.png)

然后将程序进行调试，通过第一句打印，可以获得person的地址值（我们本次得到的地址值为：006FFE4C），然后再Visual studio中去查找该块内存地址[下图]

![1573266058610](https://github.com/MSTGit/CPPNOTE/blob/master/ClassAndObject/Resource/1573266058610.png)

看到了吗？从person对象的地址值开始，连续的12个直接都是person对象的，并且三个地址值分别属于m_id，m_age，m_height成员变量的地址值。而且当前电脑的属于小端模式，所以当读取数据时，是从后往前读取的。例如m_id的值为 00 00 00 01