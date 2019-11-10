#### 封装

> 成员变量私有化，提供公共的getter和setter给外界去访问成员变量

例如以下一段代码

```C++
struct Person {
	int m_age;
};

int main() {
	Person person;
	person.m_age = 10;
	getchar();
	return 0;
}
```

声明了一个Person类，然后就可以创建一个person对象，通过对象，可以直接访问person对象的成员变量。为什么可以直接访问，在前面章节[类与对象]也已经提到过，这样做其实是右问题的。因为如果成员变量公开的话，就无法阻止使用者不规范使用该类。比如使用者可以将年龄设置为负数`person.m_age = -4`，这样对m_age赋值明显是不合理的，因为年龄不可能为负数，所以为了过滤掉不合理的值，一般将成员变量私有化，不允许外界直接赋值
![1573350039214](https://github.com/MSTGit/CPPNOTE/blob/master/Encapsulation/Resource/1573350039214.png)

为了方便外界对成员变量赋值，因此在创建类时，需要提供公共的方法，供外界setter方法设置成员变量值与getter获取成员变量值值，在setter里面，可以过滤掉外面传进来的不合理的值，在getter里面，可以获取成员变量的值，类似于这样的操作，如果你有过面向对象的开发经验，一定不会陌生

```C++
struct Person {
private:
	int m_age;
public:
	void setAge(int age) {
		if (age <= 0) {
			return;
		}
		m_age = age;
	}

	int getAge() {
		return m_age;
	}
};

int main() {
	Person person;
	person.setAge(10);
	int age = person.getAge();
	getchar();
	return 0;
}
```

这就是面向对象中，针对封装的简单介绍。