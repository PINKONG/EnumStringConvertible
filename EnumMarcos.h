//
//  EnumMarcos.h
//  OC-Enum-String-Convertible
//
//  Created by Sun on 2018/9/14.
//  Copyright © 2018年 Sun. All rights reserved.
//

#ifndef EnumMarcos_h
#define EnumMarcos_h

/*
 Reference: http://stackoverflow.com/a/202511
 Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
 For how to use, see https://github.com/PINKONG/EnumStringConvertible
 */

#pragma mark - Enum Factory Macros

/**
 utils
 */
#define PRIMITIVE_CAT(x, y) x ## y
#define CAT(x, y) PRIMITIVE_CAT(x, y)
#define GET_SEC(x, n, ...) n
#define CHECK(...) GET_SEC(__VA_ARGS__, 0)
#define PROBE(x) x, 1
#define IS_EMPTY(x) CHECK(CAT(PRIMITIVE_CAT(IS_EMPTY_, x), 0))
#define IS_EMPTY_0 PROBE()

#define IIF(c) PRIMITIVE_CAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t


/**
 注释中宏定义
 */
#define LYSS_CONNECTCHAR(a,b) a##b
#define ANNOTATION LYSS_CONNECTCHAR(/,/)

/**
 定义一个枚举case
 */
#define ENUM_VALUE(name, assign, ...) name assign,

/**
 展开后是一个switch语句的case，返回枚举值字符串
 */
#define ENUM_CASE(name, assign, ...) case name: return @#name;

/**
 展开后是一个switch语句的case，返回枚举值的描述
 */
#define ENUM_DESC(name, assign, description) @#description
#define ENUM_NAME(name, assign, ...) @#name
#define GET_ENUM_DESC(name, assign, description) \
    IIF(IS_EMPTY(description)) ( \
        ENUM_NAME(name, assign), \
        ENUM_DESC(name, assign, description) \
        )

#define ENUM_CASE_DESC(name, assign, ...) case name: return (GET_ENUM_DESC(name, assign, __VA_ARGS__));

/**
 展开后通过比较字符串，返回相应枚举case
 */
#define ENUM_STRCMP(name, assign, ...) if ([string isEqualToString:@#name]) return name;

/**
 定义枚举，声明反射函数；
 */
#define DECLARE_ENUM(EnumType, ENUM_DEF) \
typedef NS_ENUM(NSInteger, EnumType) { \
ENUM_DEF(ENUM_VALUE) \
}; \
NSString *NameFrom##EnumType(EnumType value); \
NSString *DescriptionFrom##EnumType(EnumType value); \
EnumType EnumType##FromNSString(NSString *string); \

/**
 实现实现函数；
 */
#define DEFINE_ENUM(EnumType, ENUM_DEF) \
NSString *NameFrom##EnumType(EnumType value) \
{ \
switch(value) \
{ \
ENUM_DEF(ENUM_CASE) \
default: return @""; \
} \
} \
NSString *DescriptionFrom##EnumType(EnumType value) \
{ \
switch(value) \
{ \
ENUM_DEF(ENUM_CASE_DESC) \
default: return @""; \
} \
} \
EnumType EnumType##FromNSString(NSString *string) \
{ \
ENUM_DEF(ENUM_STRCMP) \
return (EnumType)0; \
}\


#endif /* EnumMarcos_h */
