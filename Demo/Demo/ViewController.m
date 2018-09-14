//
//  ViewController.m
//  Demo
//
//  Created by Sun on 2018/9/14.
//  Copyright © 2018年 Sun. All rights reserved.
//

#import "ViewController.h"
#import "CommonEnum.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    NSString *str2 = DescriptionFromRAPDirection(RAPDirectionUp);
    NSLog(@"RAPDirectionUp has case desc: %@", str2);
    
    NSString *str31 = NameFromRAPDirection(RAPDirectionLeft);
    NSLog(@"RAPDirectionLeft has case name: %@", str31);
    NSString *str32 = DescriptionFromRAPDirection(RAPDirectionLeft);
    NSLog(@"RAPDirectionLeft has case desc: %@", str32);
    
    RAPDirection dir = RAPDirectionFromNSString(@"RAPDirectionRight");
    NSLog(@"RAPDirectionRight has case value: %zd", dir);
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
