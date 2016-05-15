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

-(bool) isStringNumber:(NSString *)stringNumber {
    NumberConverter converter;
    
    std::string stringNumberStd = [stringNumber UTF8String];
    return converter.isStringNumber(stringNumberStd);
}

- (NSString*) convertToWords:(long long)number {
    NumberConverter converter;
    
    return [NSString stringWithCString:converter.convertNumberToWords(number).c_str()
                              encoding:[NSString defaultCStringEncoding]];
    //return @"";
}

- (NSString*) convertStringNumberToWords:(NSString *)stringNumber {
    NumberConverter converter;
    
    std::string stringNumberStd = [stringNumber UTF8String];
    
    return [NSString stringWithCString:converter.convertStringNumberToWords(stringNumberStd).c_str()
                             encoding:[NSString defaultCStringEncoding]];
}


@end