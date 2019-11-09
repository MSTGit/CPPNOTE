#### this

现在有以下一段代码程序

```C++
struct Person {
	int m_age;
	void run() {
		cout << "Person :: run() " << m_age << endl;
	}
};

int main() {
	Person person;
	person.m_age = 10;
	person.run();
	getchar();
	return 0;
}
```

这段程序,我们都很清楚,首先我们创建了一个person对象,然后为对象的m_age成员变量赋了一个初始值,最后调用person对象的run函数。并且最终的打印结果是Person :: run() 10，相信各位读者是可以理解的。但是，这里有一个问题，假设我们将上面的程序进行一定的修改

```C++
struct Person {
	int m_age;
	void run() {
		cout << "Person :: run() " << m_age << endl;
	}
};

int main() {

	Person person1;
	person1.m_age = 10;
	person1.run();

	Person person2;
	person2.m_age = 20;
	person2.run();
	getchar();
	return 0;
}
```

两个Person类创建的对象，分别有属于自己的m_age成员变量，也分别调用了对应的run函数。在前面说过，person1调用的run函数与person2调用的run函数，是同一个run函数，即person1.run()与person2.run()执行的代码是同一份，对应Person类对象调用run函数后，得到的结果却不一样，其中person1.run()的结果为Person :: run() 10，person2.run()的结果为Person :: run() 20。而且前面也说过，对象的成员变量是保存在对象创建的内存区域，函数并不保存在对象中，所以，成员变量和函数是独立开的，对象的内存在栈空间，而函数的内存在代码区，那最终打印m_age的时候，是怎么知道该打印10还是20呢，这样的结果到底是怎么导致的呢？

可以这样来假设，假设当前的run函数是如下方式进行定义的，在调用函数时，可以传入一个参数，最终在函数内部，就可以获取到当前对象的成员变量了

```C++
void run(Person *person) {
    cout << "Person :: run() " << person->m_age << endl;
}
```

后面调用的时候，就可以通过这种方式来进行调用

```C++
struct Person {
	int m_age;
	void run(Person *person) {
		cout << "Person :: run() " << person->m_age << endl;
	}
};

int main() {

	Person person1;
	person1.m_age = 10;
	person1.run(&person1);

	Person person2;
	person2.m_age = 20;
	person2.run(&person2);
	getchar();
	return 0;
}
```

这样就可以办到，通过函数参数中的指针，间接的访问到该对象的存储空间，然后访问对象的成员变量了。所以，这是一种在函数里面可以访问到对象成员变量的一种方式。但是，如果每次声明函数时，都需要定义一个这样的参数，在调用函数时，都需要传入这个参数的话，就太麻烦了。好在编译器已经把这一切都做了，编译器在每个函数里面，都提供了一个this指针，并且该指针指向当前调用该函数的对象。所以可以这样理解，某个对象调用函数时，都会偷偷的将该对象赋值给this指针。即

```C++
struct Person {
	int m_age;
	void run() {
        //this = &person1; 假想的
		cout << "Person :: run() " << m_age << endl;
	}
};

int main() {

	Person person1;
	person1.m_age = 10;
	person1.run();
	getchar();
	return 0;
}
```

可以理解为函数中默认有一个隐式参数this指针，并且该隐式参数this指针存储着函数调用者的地址，所以上面的代码也可以这样写

```C++
struct Person {
	int m_age;
	void run() {
		cout << "Person :: run() " << this->m_age << endl;
	}
};

int main() {

	Person person1;
	person1.m_age = 10;
	person1.run();
	getchar();
	return 0;
}
```

现在就来看看具体是怎么实现的。首先假设有一个全局的函数func，然后再main函数中调用该func函数，对比与调用run函数的区别

```C++
void func() {

}

int main() {
	func();
	Person person1;
	person1.m_age = 10;
	person1.run();

	Person person2;
	person2.m_age = 20;
	person2.run();
	getchar();
	return 0;
}
```

相信你一定能想象，现在func函数生成的汇编是什么样的。对的！没错call [函数地址]，并且来看一下func函数与run函数的区别

![1573278480951](https://github.com/MSTGit/CPPNOTE/blob/master/this/Resource/1573278480951.png)

从run函数调用生成汇编代码中看到，在执行call指令之前，执行了lea操作。lea指令的作用是取出person1的内存地址，然后将内存地址，赋值给了ecx寄存器。将地址存到ecx寄存器以后，后面是怎么获取的呢？可以通过单步调试进入到call对应的函数中。

![1573279172949](https://github.com/MSTGit/CPPNOTE/blob/master/this/Resource/1573279172949.png)

在这一段代码中，我们看到有一句mov指令 `mov dword ptr [this],ecx`，这句指令是将ecx里面存储的数据，放到[this]指针的存储空间，这样，this指针就成功的指向了person1。这样就可以在函数里面，通过this指针访问person1里面的成员变量了。

现在将整个流程梳理一遍：

1. 在调用run函数之前，先将person1对象的地址，存放到了ecx寄存器
2. 调用run函数
3. 在函数内部，将ecx寄存器中存储的person1的地址值，存放到this指针对应的存储空间
4. 通过this指针，访问person成员变量

但是你可能会这样想，在平时编码的过程中，并没有直接通过this指针来访问函数的成员变量，而是直接访问的。这个问题其实是语法糖，在表面上看，没有用到this，但是实际上用到了this，只不过编译器处理以后，我们可以省略，所以下面的两种写法是等价的。

```C++
void run() {
    cout << "Person :: run() " << this->m_age << endl;
}
void run() {
    cout << "Person :: run() " << m_age << endl;
}
```

究竟是不是等价的，看以下汇编就知道了。所以将这段代码转为汇编

```C++
struct Person {
	int m_age;
	void run() {
		cout << "Person :: run() " << m_age << endl;
	}
};

void func() {

}

int main() {
	func();
	Person person1;
	person1.m_age = 10;
	person1.run();

	Person person2;
	person2.m_age = 20;
	person2.run();
	getchar();
	return 0;
}
```

生成汇编

![1573280669320](https://github.com/MSTGit/CPPNOTE/blob/master/this/Resource/1573280669320.png)

run函数生成的汇编

![1573280723448](https://github.com/MSTGit/CPPNOTE/blob/master/this/Resource/1573280723448.png)

最终发现，两段代码，生成的汇编代码是完全一样的。

好的。现在已经了解到this指针的本质，那么问题来了，可以利用this.m_age来访问成员变量吗？

答：不可以，因为this是指针，必须用this->m_age来访问。

#### 指针访问对象成员的本质

🤔下面这段代码，最后打印出来的每个成员变量的值是多少？

```c++
struct Person {
	int m_id;
	int m_age;
	int m_height;
	void display() {
		cout << "id =  " << m_id
			<< ", age = " << m_age 
			<< ", height = " << m_height << endl;
	}
};

int main() {
	Person person;
	person.m_id = 10;
	person.m_age = 20;
	person.m_height = 30;
	person.display();
	getchar();
	return 0;
}
```

话不多说，直接看以下生成的汇编代码。

首先，为成员变量赋值的汇编非常简单[下图]，直接将立即数存放到成员变量对应的存储空间。

![1573281833055](https://github.com/MSTGit/CPPNOTE/blob/master/this/Resource/1573281833055.png)

为了回答上面的问题，还需要再来看看指针变量是如何访问成员变量的

```C++
struct Person {
	int m_id;
	int m_age;
	int m_height;
	void display() {
		cout << "id =  " << m_id
			<< ", age = " << m_age 
			<< ", height = " << m_height << endl;
	}
};

int main() {
	Person person;
	person.m_id = 10;
	person.m_age = 20;
	person.m_height = 30;
	person.display();

	Person* p = &person;
	p->m_id = 10;
	p->m_age = 20;
	p->m_height = 30;
	getchar();
	return 0;
}
```

对应的汇编代码

![1573283024857](https://github.com/MSTGit/CPPNOTE/blob/master/this/Resource/1573283024857.png)

补充：上图中eax中存储的即为对象person的地址值，然后根据对象的地址 + 成员变量的偏移，就能找到对应的成员变量。

如何利用指针间接访问所指向对象的成员变量原理总结：

1. 从指针中取出对象的地址
2. 利用对象的地址 + 成员变量的偏移量，计算出成员变量的地址
3. 根据成员变量的地址访问成员变量的存储空间

说到这里，我想已经知道上面display函数的本质了吧?

前面讲到，以下两种写法是等价的

```C++
void display() {
    cout << "id =  " << m_id
        << ", age = " << m_age 
        << ", height = " << m_height << endl;
}
void display() {
    cout << "id =  " << this->m_id
        << ", age = " << this->m_age 
        << ", height = " << this->m_height << endl;
}
```

所以，答案我想已经有了吧！

现在已经知道，指针访问成员变量是通过偏移来访问的，那下面的这个打印结果又是多少呢？

```c++
struct Person {
	int m_id;
	int m_age;
	int m_height;
	void display() {
		cout << "id =  " << m_id
			<< ", age = " << m_age 
			<< ", height = " << m_height << endl;
	}
};

int main() {
	Person person;
	person.m_id = 10;
	person.m_age = 20;
	person.m_height = 30;
	Person* p = (Person*)&person.m_age;
	p->m_id = 40;
	p->m_age = 50;
	person.display();
	getchar();
	return 0;
}
```

打印的结果是10,40,50。

如果将上面代码中的`person.display()`换为`p->display()`得到的结果，又是什么呢？