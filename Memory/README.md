#### 内存空间的布局

每个应用都有自己独立的内存空间，其内存空间一般都有以下几大区域

1. 代码段（代码区）
   - 用来存放代码
   - 只读
2. 数据段（全局区）
   - 用于存放全局变量
3. 栈空间
   - 每调用一个函数，就会为函数分配一段连续的栈空间，等函数调用完毕后，会自动回收这段栈空间
   - 自动分配和回收
4. 堆空间
   - 需要主动申请和释放

所以，某应用的内存空间（主要），可以通过下图来进行表示

![1573352121314](https://github.com/MSTGit/CPPNOTE/blob/master/Memory/Resource/1573352121314.png)

![1573352254933](https://github.com/MSTGit/CPPNOTE/blob/master/Memory/Resource/1573352254933.png)

![1573352268550](https://github.com/MSTGit/CPPNOTE/blob/master/Memory/Resource/1573352268550.png)

![1573352282467](https://github.com/MSTGit/CPPNOTE/blob/master/Memory/Resource/1573352282467.png)

通过前面的介绍，已经知道，如果是函数调用，局部变量，使用的是栈空间，如果该变量，是所有人都可以访问的，可以使用全局区，编写的代码，存放在代码区。那堆空间有什么用呢？

#### 堆空间

在程序运行过程中，为了能够**自由控制**内存的**生命周期**，**大小**，会经常使用堆空间的内存。

所以在C++中，可以通过下面的方式，来申请\释放内存

1. malloc \ free
   例如现在向堆空间申请4个字节的存储空间。然后将申请的内存空间，用来存放int变量。然后就可以往申请的空间中存放数据了。然后使用完了以后，使用free来回收申请的堆空间内存。需要注意：在释放内存时，请不要过度释放

   ```C++
   int* p = (int *)malloc(4);
   *p = 10;
   free(p);
   ```

   其中指针与申请堆空间内存的关系如下（地址值仅供参考，X86环境 32bit）

   ![1573372716080](https://github.com/MSTGit/CPPNOTE/blob/master/Memory/Resource/1573372716080.png)

   下面两种申请堆空间内存的区别

   ```c++
   int* p = (int*)malloc(4);
   char* p = (char*)malloc(4);
   ```

   1. int 这种申请方式，在堆空间中申请了4个直接的内存空间，并且最后是使用的int类型来指向该空间，后面再访问该内存空间时，就会按照int的寻址大小来进行访问，可以访问4个字节。
   2. char这种申请方式，虽然在堆空间申请了4个直接的内存空间，但是使用的是char类型来指向该空间，由于char类型的寻址范围是1字节，所以char类型的指针只能访问堆空间中的第一个字节。

2. new\delete

   ```C++
   int* p = new int;
   *p = 10;
   delete p;
   ```

3. new[]\delete[]

   ```C++
   int* p = new int[];
   *p = 10;
   delete[] p;
   ```

堆空间申请注意点：

1. 申请堆空间成功后，会返回那一段内存空间的地址
2. 申请和释放必须是1对1的关系，不然可能会存在内存泄漏

现在的很多高级编程语言不需要开发人员去管理内存（比如Java），屏蔽了很多内存细节，利弊同时存在。

- 利：提高开发效率，避免内存使用不当或泄漏
- 弊：不利于开发人员了解本质，永远停留在API调用和表层语法糖，对性能优化无从下手

#### 堆空间的初始化

假设现在有这样一段代码

```C++
int* p = (int*)malloc(4);
```

当申请完内存以后，堆空间有没有将内存进行初始化呢？如果现在在visual studio里面去访问指针指向的存储空间的话，会发现结果是一堆乱七八糟的值，所以在visual studio里面，是没有初始化的。如果这个时候，想在申请完堆空间以后，就初始化堆空间中的内存，可以使用下面的这种方式来初始化

```C++
int size = sizeof(int) * 10;
int* p1 = (int*)malloc(size);
int* p2 = (int*)malloc(size);
memset(p2, 0, size);
```

通过这种方式，就可以将*p2的每一个字节都初始化为0，但是由于上面没有对 *p1进行初始化，所以 *p1没有被初始化。

初始化总结：

```C++
int* p1 = new int;			//未被初始化
int* p2 = new int();		//被初始化为0
int* p3 = new int(5);		//被初始化为5
int* p4 = new int[3];		//数组元素未被初始化
int* p5 = new int[3]();		//3个数组元素都被初始化为0
int* p6 = new int[3]{};		//3个数组元素都被初始化为0
int* p7 = new int[3]{5};	//数组首元素被初始化为5，其他元素被初始化为0
```

###### memset的作用

memset函数是将较大数据结构（比如对象，数组等）内存清零的比较快的方法。

比如现在有一个如下的Person对象，需要对对象中的每个成员变量都清零的话，就可以使用memset来快速清零。

```c++
struct Person {
	int m_id;
	int m_age;
	int m_height;
};

void func(){
	Person person;
	person.m_id = 1;
	person.m_age = 20;
	person.m_height = 190;
	memset(&person, 0, sizeof(person));
    
    Person persons[] = { {1,20,190},{1,18,180} };
	memset(persons, 0, sizeof(persons));
}
```

#### 对象的内存

一个对象被创建出来以后，可以存在于3个地方

- 全局区（数据段）：全局变量
- 栈空间：函数里面的局部变量
- 堆空间：动态申请内存（malloc,new等）

如下代码所示：

```C++
//全局区
Person g_person;

int main() {
	//栈空间
	Person person;
	//堆空间
	Person* p = new Person;
	return 0;
}
```

所以，通过本文的讲解，对内存有更深的理解了吗？