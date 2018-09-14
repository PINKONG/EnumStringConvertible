//
//  CommonEnum.h
//  Demo
//
//  Created by Sun on 2018/9/14.
//  Copyright © 2018年 Sun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EnumMarcos.h"

#define RAP_DIRECTION(XX) \
XX(RAPDirectionUp, ) \
XX(RAPDirectionDown, ) \
XX(RAPDirectionLeft, = 50, 左) \
XX(RAPDirectionRight, = 100, 右) \

DECLARE_ENUM(RAPDirection, RAP_DIRECTION)

