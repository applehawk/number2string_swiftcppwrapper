//
//  NumberConverterCPP.hpp
//  NumberConverterSwift
//
//  Created by Teller.Vlad on 14.05.16.
//  Copyright © 2016 Teller.Vlad. All rights reserved.
//

#pragma once
#include <string>
#include <stdio.h>

class NumberConverter {
private:
    long long m_number;
protected:
    std::string convertLess100Number( int digitTwo, int digitOne, long long processNumber );
    void number2Digits(int* digits, long long number, int max_digits_count);
    std::string convertN10Number( long long processNumber );
public:
    NumberConverter(long long number);
    std::string convertToWords();
};