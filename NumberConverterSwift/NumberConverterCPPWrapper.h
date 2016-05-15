//
//  NumberConverterCPPWrapper.h
//  NumberConverterSwift
//
//  Created by Teller.Vlad on 14.05.16.
//  Copyright © 2016 Teller.Vlad. All rights reserved.
//

#ifndef NumberConverterCPPWrapper_h
#define NumberConverterCPPWrapper_h
#import <Foundation/Foundation.h>

@interface NumberConverterCPPWrapper : NSObject

- (NSString*) convertToWords:(long long) number;
@end

#endif /* NumberConverterCPPWrapper_h */
