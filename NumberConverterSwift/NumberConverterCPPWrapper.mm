//
//  NumberConverterCPPWrapper.m
//  NumberConverterSwift
//
//  Created by Teller.Vlad on 14.05.16.
//  Copyright © 2016 Teller.Vlad. All rights reserved.
//

/*
 - (id) initWithNumber:(long long)number;
 
 - (NSString*) convertToWords;
 */

#import "NumberConverterCPPWrapper.h"
#include "NumberConverterCPP.hpp"

NumberConverter* converter = NULL;

@implementation NumberConverterCPPWrapper

- (NSString*) convertToWords:(long long)number {
    NumberConverter converter(number);
    
    return [NSString stringWithCString:converter.convertToWords().c_str()
                              encoding:[NSString defaultCStringEncoding]];
}


@end