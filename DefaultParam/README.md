#### 默认参数

例如我们现在有这样一个函数

```C++
int sum(int v1, int v2) {
	return v1 + v2;
}
```

当我们调用该函数时，传入参数，可以得到我们想要的结果。

如果我们为函数中的参数设置上默认参数后

```C++
int sum(int v1 = 5, int v2 = 6) {
	return v1 + v2;
}
```

这个时候，就代表形参v1的值，默认为5，形参v2的值，默认为6。为参数设置好默认参数以后，我们就可以通过以下这些方式，来调用该函数

```c++
sum();
sum(10);
sum(10, 20);
```

这三种调用方式，均是正确的。
第一种调用方式：我们什么都不传，由于函数有默认值，此时v1的值为5，v2的值为6；
第二种调用方式：由于我们只传了一个参数，因此就会将该参数的值赋值给v1，此时v1的值为10，v2的值为6；
第三种调用方式：这种情况，就会把值分别赋值给每一个参数，此时v1的值为10，v2的值为20；

所以，C++允许函数设置默认参数，在调用时，可以根据情况，省略实参，并有如下规则：

1. 默认参数只能按照从右到左的顺序进行设置；例如下列的这些函数声明方式是错误的

   ```C++
   int sum(int v1 = 5, int v2) {
   	return v1 + v2;
   }
   void func(int v1, int v2 = 5, int v3) {
   
   }
   void func(int v1 = 6, int v2, int v3 = 10) {
   
   }
   ```

   正确写法为

   ```C++
   int sum(int v1, int v2 = 5) {
   	return v1 + v2;
   }
   void func(int v1, int v2 = 5, int v3 = 5) {
   
   }
   void func(int v1 = 6, int v2 = 5, int v3 = 10) {
   
   }
   ```

   

2. 如果函数同时有声明，实现，默认参数只能放在函数的声明中；因此下列的这种定义方式是错误的

   ```C++
   int sum(int v1 = 5, int v2 = 6);
   int sum(int v1 = 5, int v2 = 6) {
   	return v1 + v2;
   }
   ```

   正确写法为

   ```C++
   int sum(int v1 = 5, int v2 = 6);
   int sum(int v1, int v2) {
   	return v1 + v2;
   }
   ```

   

3. 默认参数的值可以是常亮，全局符号（全局变量，函数名）；例如

   ```C++
   int age = 20;
   int sum(int v1 = 5, int v2 = age);
   int sum(int v1, int v2) {
   	return v1 + v2;
   }
   
   void test(int a) {
   	cout << "test(int) - " << a << endl;
   }
   
   void func(int v1, void(*p)(int) = test) {
   	p(v1);
   }
   ```

##### 默认参数的价值

假设我们现在有这样一种情况，调用某个函数时，其中一个函数经常在变化，另外一个参数偶尔发生变化，如我们调用上面的sum函数时

```C++
sum(1, 20);
sum(2, 20);
sum(3, 20);
sum(4, 20);
sum(5, 20);
sum(6, 15);
sum(7, 20);
```

我们就可以在定义函数时，将偶尔发生变化的参数设置默认参数

```C++
int sum(int v1, int v2 = 20) {
	return v1 + v2;
}
```

设置完以后，在调用函数并且该参数的值为默认参数的值时，就可以不用传该参数，如下面这种调用方式与上面的方式等价

```
sum(1);
sum(2);
sum(3);
sum(4);
sum(5);
sum(6, 15);
sum(7);
```

因此，如果函数的

##### 函数重载，默认参数可能会产生冲突，二义性（建议优先选择使用默认参数）

例如下面这种情况，两个函数，首先构成了函数重载，然后再其中一个函数中添加了一个默认参数，最终在main函数中调用display函数时，就会发生错误。因为这样写，调用任意一个函数都符合条件。因此最终不确定调用哪个函数。

```C++
void display(int a, int b = 20) {
	cout << "a is " << a << endl;
}

void display(int a) {
	cout << "a is " << a << endl;
}

int main() {
	display(10);
	return 0;
}
```

#### 默认参数的本质

首先，假设我们定义了如下的函数与调用方式

```C++
int sum(int v1, int v2) {
	return v1 + v2;
}

int main() {
	sum(1, 2);
	sum(3, 4);
    return 0;
}
```

在我们没有使用默认参数时，我们来看看该代码对应生成的汇编代码

![1572869797606](https://github.com/MSTGit/CPPNOTE/blob/master/DefaultParam/Resource/1572869797606.png)

我们看到，调用一次sum函数，会生成4句对应的汇编代码，其中我们看到call指令，直接调用的是sum函数，并且我们也可以发现，两次call指令，调用的函数，对应的地址是一样的。但是对应的参数是不一样的，所以在调用sum函数之前，会通过push指令，将参数入栈传参，然后再调用sum函数。

如果我们现在为函数设置了默认参数值

```
int sum(int v1, int v2 = 4) {
	return v1 + v2;
}

int main() {
	sum(1);
	return 0;
}
```

运行成功后，转到反汇编的结果为

![1572870512661](https://github.com/MSTGit/CPPNOTE/blob/master/DefaultParam/Resource/1572870512661.png)

通过结果，我们发现，如果我们调用有默认参数的函数是，如果我们不传默认参数的话，在程序运行时，也会将默认参数通过push指令，将参数传入函数中，最终传的参数也是2个。那么如果我们换一种方式调用呢？如

```
int sum(int v1, int v2 = 4) {
	return v1 + v2;
}

int main() {
	sum(1);
	sum(1, 4);
	return 0;
}
```

运行成功后，转到反汇编的结果为

![1572870832415](https://github.com/MSTGit/CPPNOTE/blob/master/DefaultParam/Resource/1572870832415.png)

通过认真观察，我们发现，两句函数调用，最终生成的汇编代码是相同的，所以上面的两种函数调用是等价的。