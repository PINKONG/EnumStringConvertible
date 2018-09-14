# OC枚举值到字符串转换

## 缘起
Objective-C中经常需要将枚举转换成对应的字符串类型。平时一般用if或switch语句返回枚举值对应的字符串，高级一点的呢就使用字典做映射，如：

```
typedef NS_ENUM(NSUInteger, RAPDirection) {
    RAPDirectionUp,
    RAPDirectionDown,
    RAPDirectionLeft,
    RAPDirectionRight
};

- (NSString *)stringForRAPDirection:(RAPDirection)type {
    static NSDictionary *map = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        map = @{
            @(RAPDirectionUp): @"上",
            @(RAPDirectionDown): @"下",
            @(RAPDirectionLeft): @"左",
            @(RAPDirectionRight): @"右",
        };
    });
    return map[@(type)] ?: @"unknown";
}


```

相比之下, Swfit要简单的多。Swift枚举类型引入了Raw Value的概念，每个枚举case的Raw Value可以是其case name。假设有case up，则up.rawValue = "上"。

那有没有更简单的一步到位的方法，在定义时候就榜单相应的字符串呢？看到一篇文章[OC枚举值到字符串转换](https://www.jianshu.com/p/5919e5ef5034), 作者用`宏替换`实现了将枚举值映射为对应的字符串，如枚举值`RAPDirectionUp`映射成@"RAPDirectionUp". 在此基础上，我增加了枚举值映射成自定义文字的功能，如`RAPDirectionUp`映射成@"上"。

---

##安装
==============

### CocoaPods

1. 在 Podfile 中添加  `pod 'EnumStringConvertible'`。
2. 执行 `pod install` 或 `pod update`。
3. 导入 \<EnumStringConvertible/EnumMarcos.h\>。

## A. 使用

这套宏的用法分为两步：

### A.1 在.h文件中定义枚举，声明反射函数

```c
// M1
#define RAP_DIRECTION(XX) \
XX(RAPDirectionUp, ) \
XX(RAPDirectionDown, ) \
XX(RAPDirectionLeft, = 50, 左) \
XX(RAPDirectionRight, = 100, 右) \

// M2
DECLARE_ENUM(RAPDirection, RAP_DIRECTION)
```
	
- M1生成多个枚举case。枚举case的定义格式为XX(name, assign)，name即case name；assign即对应整数值，格式必须为`= Integer`，不填表示使用默认值；第三个参数为要映射的描述，不填则返回name。

- M2定义枚举，声明反射函数。反射函数的有三个：
	- 根据case获取case name：NameFromRAPDirection(RAPDirection value);
	- 根据case获取case 描述： DescriptionFromRAPDirection(RAPDirection value);
	- 根据case name获取case：RAPDirectionFromNSString(NSString *string);

### A.2 在.m文件中实现反射函数

```c
DEFINE_ENUM(RAPDirection, RAP_DIRECTION)
```
- RAPDirection和RAP_DIRECTION要与.h中的宏对应。RAPDirection是枚举类型名称，RAP_DIRECTION是宏，展开后变成多个枚举case。

### A.3 函数调用

尝试使用：


    NSString *str2 = DescriptionFromRAPDirection(RAPDirectionUp);
    NSLog(@"RAPDirectionUp has case desc: %@", str2);
    
    NSString *str31 = NameFromRAPDirection(RAPDirectionLeft);
    NSLog(@"RAPDirectionLeft has case name: %@", str31);
    NSString *str32 = DescriptionFromRAPDirection(RAPDirectionLeft);
    NSLog(@"RAPDirectionLeft has case desc: %@", str32);
    
    RAPDirection dir = RAPDirectionFromNSString(@"RAPDirectionRight");
    NSLog(@"RAPDirectionRight has case value: %zd", dir);


输出结果：

```
RAPDirectionUp has case desc: RAPDirectionUp
RAPDirectionLeft has case name: RAPDirectionLeft
RAPDirectionLeft has case desc: 左
RAPDirectionRight has case value: 100
```


## 参考资料

1. [示例代码](https://github.com/PINKONG/EnumStringConvertible)
2. [OC枚举值到字符串转换](https://www.jianshu.com/p/5919e5ef5034)
3. [宏定义黑魔法-从入门到奇技淫巧](http://feng.zone/2017/05/21/宏定义黑魔法-从入门到奇技淫巧-4/)
4. [pfultz2/Cloak](https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms)
5. [Easy way to use variables of enum types as string in C?
](https://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c/202511#202511)
