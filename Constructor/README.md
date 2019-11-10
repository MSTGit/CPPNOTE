#### 构造函数（Constructor）

构造函数这个概念，相信很多童鞋都听过，只要是有过面向对象的开发经验，一定不会陌生。

> 构造函数（也叫构造器），在对象创建你的时候自动调用，一般用于完成对象的初始化工作

例如下列的Person类在创建对象时的初始化，创建出对象以后，希望每个对象刚创建出来时的年龄都是0，所以可能会这么做

```C++
struct Person {
	int m_age;
};
int main() {
	Person person;
	person.m_age = 0;

	Person person2;
	person2.m_age = 0;

	Person person3;
	person2.m_age = 0;
	getchar();
	return 0;
}
```

但是，通过这种方式来初始化，发现太麻烦了。一般的话，会写一个构造函数，像这种初始化工作，都在构造函数中去完成，这样就不用每次创建完对象，都去手动初始化成员变量。所以上面这段代码，使用构造函数的话，可以这样去修改。

```C++
struct Person {
	int m_age;
	Person() {
		m_age = 0;
	}
};
int main() {
	Person person;

	Person person2;

	Person person3;
	getchar();
	return 0;
}
```

构造函数的特点：

- 函数名与类名相同，无返回值（void都不能写），可以有参数，可以重载，可以有多个构造函数。

- 一旦自定义了构造函数，必须用其中一个之第一的构造函数来初始化对象，所以下面这种写法是错误的。

  ```C++
  struct Person {
  	int m_age;
  	Person(int age) {
  		m_age = 0;
  	}
  };
  int main() {
  	Person person;
  
  	Person person2;
  
  	Person person3;
  	getchar();
  	return 0;
  }
  ```

注意：通过malloc分配的对象，不会调用构造函数；例如下列的方式来创建对象

```C++
struct Person {
	int m_age;
};

int main() {
	Person* p = (Person*)malloc(sizeof(Person));
	p->m_age = 10;
	getchar();
	return 0;
}
```

所以，在C++里面，如果想要将对象的内存放到堆空间，千万不要使用malloc的方式来创建对象。

**一个广为流传的，很多教程\书籍都推崇的错误结论：**

~~默认情况下，编译器会为每一个类生成空的无参的构造函数~~，表示的意思是这样的，下列代码中，就算现在不为该类创建构造函数，编译器都会为该类生成一个无参的构造函数`Person() {}`

```C++
struct Person {
	int m_age;
};

int main() {
	Person person;
	getchar();
	return 0;
}
```

这个结论是错的！

假设现在，自己有定义这个无参的构造函数，然后来看看生成的汇编代码

```C++
struct Person {
	int m_age;
	Person() {};
};

int main() {
	Person person;
	getchar();
	return 0;
}
```

对应的汇编代码

![1573396334742](https://github.com/MSTGit/CPPNOTE/blob/master/Constructor/Resource/1573396334742.png)

从图上可以看到，如果在代码中有定义无参的构造函数，在创建Person对象是，编译器是会调用该无参构造函数的。

如果现在不自己定义无参的构造函数，生成的汇编代码

![1573396377931](https://github.com/MSTGit/CPPNOTE/blob/master/Constructor/Resource/1573396377931.png)

并没有看到调用构造函数，直接将m_age的10赋值到了person对象的存储空间，也就意味着，刚刚创建完person对象，根本就没有调用无参的构造函数。

但是某些情况会调用无参的构造函数，例如将上面代码修改为下列代码时

```C++
struct Person {
	int m_age = 0;
};

int main() {
	Person person;
	person.m_age = 10;
	getchar();
	return 0;
}
```

最终转成的汇编

![1573396731371](https://github.com/MSTGit/CPPNOTE/blob/master/Constructor/Resource/1573396731371.png)

看到，这时候不一样了，明显看到有call Person，这个时候就调用了一个构造函数，这个时候就会为你生成一个空的无参的构造函数。所以上面那个错误的结论是不严谨的，需要改为
**在某些特定的情况下， 编译器才会为类生成空的无参的构造函数**；哪些特定的情况呢？后面章节会提到，情况比较多

##### 构造函数的调用

同样现在定义一个Person类，不同的是现在有2个构造函数

```C++
struct Person {
	int m_age;
	
	Person() {
		cout << "Person()" << endl;
	};

	Person(int age) {
		cout << "Person(int age)" << endl;
	};
};
```

然后再定义9个person对象，请问，下列的这些person对象，会分别调用哪些构造函数

```C++
Person g_person0;
Person g_person1();
Person g_person2(10);
int main() {
	Person person0;
	Person person1();
	Person person2(20);

	Person* p0 = new Person;
	Person* p1 = new Person();
	Person* p2 = new Person(30);
	getchar();
	return 0;
}
```

如果按照前面的思路，如果没有传参数，则会默认调用无参的构造函数，有传参数的话，则会调用有1个参数的构造函数。最终的话，应该有6个对象会调用无参的构造函数，3个对象会调用有参的构造函数。这个时候，把程序运行起来，看一下最终的效果是不是期望的效果。打印结果[下图]

![1573397940600](https://github.com/MSTGit/CPPNOTE/blob/master/Constructor/Resource/1573397940600.png)

现在来数一数，发现有参的构造函数确实调用了3次，但是无参的构造函数，最终只调用了4次，也就是说，所有调用构造函数的次数也只有7次，明明创建了9个person，但是为什么只调用了7次构造函数呢？

前面讲到，在初始化对象时，如果有自定义构造函数，必须使用其中一个构造函数来创建对象，所以，只要有创建person对象，那么肯定会有调用构造函数，既然从结果上看，只有7次调用构造函数，说明最终只创建了7个person对象，有2次并没有创建person对象。答案是`Person g_person1()`与`Person person1()`并没有创建person对象，原因是这两句代码，是函数声明，例如`int sum()`这样声明一个函数一样