#### const成员

const成员：被const修饰的成员变量，非静态成员函数

像在平时开发中，可以通过以下的方式来定义成员变量， 并且在需要修改的时候，修改该成员变量的值

```C++
class Car {
public:
	int m_price;
	void run() {
		cout << "run()" << endl;
		m_price = 10;
	}
};

int main() {
	Car car;
	car.m_price = 20;
	getchar();
	return 0;
}
```

但是，如果一旦对成员变量加上const修饰，则可以成为const成员变量，const成员有一个很明显的特点，就是不能修改变量的值。所以当成员变量增加const进行修饰的话，后面修改成员变量地方的代码就会报错。

##### const成员变量

1. 必须初始化（类内部初始化），可以在声明的时候直接初始化赋值。即可以通过这种方式来初始化

   ```c++
   class Car {
   public:
   	const int m_price = 10;
   	void run() {
   		cout << "run()" << endl;
   	}
   };
   ```

2. 非static的const成员变量还可以在初始化列表中初始化。所以也可以通过这种方式进行初始化

   ```C++
   class Car {
   public:
   	const int m_price;
   	Car() :m_price(0) {
   	}
   	void run() {
   		cout << "run()" << endl;
   	}
   };
   ```

##### const成员函数（非静态）

const成员函数有以下特点

1. const关键字写在参数列表后面，函数的声明和实现都必须带const，即可以通过这种方式来定义一个const成员函数

   ```C++
   class Car {
   public:
   	int m_price;
   	void run() const{
   		cout << "run()" << endl;
   	}
   };
   ```

2. 内部不能修改非static成员变量；所以不可以通过这种方式来对非静态成员变量进行修改

   ```C++
   class Car {
   public:
   	int m_price;
   	void run() const{
   		cout << "run()" << endl;
   		m_price = 0;//这种方式是不允许的
   	}
   };
   ```

   除非对成员变量加上static进行修饰。所以这里const的作用是限制了函数内部，不允许修改普通类型的成员变量

3. 内部只能调用const成员函数，static成员函数；所以在const修饰的成员函数内部，不允许通过下面的方式来调用函数

   ```C++
   class Car {
   public:
   	int m_price;
   	void run() const{
   		cout << "run()" << endl;
   		test();//这种调用方式是不允许的
   	}
   	void test() {
   	}
   };
   ```

   除非对test函数使用const或者static进行修饰

4. 非const成员函数可以调用const成员函数

5. const成员函数和非const成员函数构成重载；即下面两个函数，构成了重载关系

   ```C++
   class Car {
   public:
   	int m_price;
   	void run() const{
   		cout << "run() const" << endl;
   	}
   	void run() {
   		cout << "run()" << endl;
   	}
   };
   int main() {
   	Car car;
   	car.run();
   	getchar();
   	return 0;
   }
   ```

   

6. 非const对象（指针）优先调用非const成员函数

   ```C++
   int main() {
   	Car car;
   	car.run();//调用普通的成员函数
   
   
   	const Car car2;
   	car2.run();//调用const修饰的静态成员函数
   	getchar();
   	return 0;
   }
   ```

   如果没有普通的成员函数，这调用const修饰的成员函数

7. const对象（指针）只能调用const成员函数，static成员函数

   ```C++
   class Car {
   public:
   	int m_price;
   	void run() const{
   		cout << "run() const" << endl;
   	}
   	void run() {
   		cout << "run()" << endl;
   	}
       static void test() {
   	}
   };
   int main() {
   	Car car;
   	car.run();//调用普通的成员函数
   
   	const Car car2;
   	car2.run();//调用const修饰的静态成员函数
       car2.test();
   	getchar();
   	return 0;
   }
   ```

   