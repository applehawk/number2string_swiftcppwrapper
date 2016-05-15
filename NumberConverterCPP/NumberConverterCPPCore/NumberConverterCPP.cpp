//
//  NumberConverterCPP.cpp
//  NumberConverterSwift
//
//  Created by Teller.Vlad on 14.05.16.
//  Copyright © 2016 Teller.Vlad. All rights reserved.
//

#include "NumberConverterCPP.hpp"

#include <iostream>
#include <climits>
#include <regex>

std::string numberWord[] = {
    "zero", //0
    "one", //1
    "two", //2
    "three", //3
    "four", //4
    "five", //5
    "six", //6
    "seven", //7
    "eight", //8
    "nine", //9
    "ten", //10
    "eleven", //11
    "twelve", //12
    "thirteen",//13
    "fourteen",//14
    "fifteen",//15
    "sixteen",//16
    "seventeen",//17
    "eighteen",//18
    "nineteen",//19
    "twenty"
};

std::string num10N[] = {
    "nil",
    "ten",
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety",
};

std::string num10PowNNames[] = {
    "",
    "hundred",
    "thousand",
    "million",
    "billion",
    "trillion",
};

enum NUM10_POW_NAME {
    ZERO = 0,
    HUNDREDS = 1,
    THOUSAND = 2,
    MILLION = 3,
    BILLION = 4,
    TRILLION = 5,
};

// generic solution
template <class T>
int numDigits(T number)
{
    int digits = 0;
    if (number <= 0) digits = 1; // remove this line if '-' counts as a digit
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}


// partial specialization optimization for 32-bit numbers
template<>
int numDigits(int32_t x)
{
    if (x == INT_MIN) return 10 + 1;
    if (x < 0) return numDigits(-x) + 1;
    
    if (x >= 10000) {
        if (x >= 10000000) {
            if (x >= 100000000) {
                if (x >= 1000000000)
                    return 10;
                return 9;
            }
            return 8;
        }
        if (x >= 100000) {
            if (x >= 1000000)
                return 7;
            return 6;
        }
        return 5;
    }
    if (x >= 100) {
        if (x >= 1000)
            return 4;
        return 3;
    }
    if (x >= 10)
        return 2;
    return 1;
}

std::string NumberConverter::convertLess100Number( int digitTwo, int digitOne, long long processNumber )
{
    std::string wordsResult = "";
    
    if (processNumber <= 20) {
        wordsResult += numberWord[processNumber];
    }
    
    if (processNumber < 100 && processNumber > 20) {
        wordsResult += num10N[ digitTwo ];
        if (digitOne != 0) {
            wordsResult += "-" + numberWord[ digitOne ];
        }
    }
    return wordsResult;
}
    
void NumberConverter::number2Digits(int* digits, long long number, int max_digits_count) {
    int iDigit = 0;
    long long processNumber = number;
    while (processNumber > 0 && iDigit < max_digits_count) {
        int numberN10 = processNumber % 10;
        digits[iDigit] = numberN10;
        processNumber = processNumber / 10;
        iDigit += 1;
    }
}
//0...999
std::string NumberConverter::convertN10Number( long long processNumber, bool allowZero) {
    std::string wordsResult;
    int digits2[3];
    memset(digits2, 0, sizeof(int)*3);
    //processNumber = m_number % 1000000000;
    //processNumber = processNumber / 1000000;
    //int iNumDigits = numDigits(processNumber);
    number2Digits(digits2, processNumber, 3);
    
    if (digits2[2] != 0) {
        wordsResult += numberWord[ digits2[2] ] + " " + num10PowNNames[ HUNDREDS ];
        processNumber = processNumber % 100;
        if (processNumber > 0) {
            wordsResult += " and ";
        }
    }
    
    if (processNumber > 0 || allowZero == true) {
        wordsResult += convertLess100Number(digits2[1], digits2[0], processNumber);
    }
    
    /*processNumber = m_number % 1000000;
     if (processNumber > 0) {
     wordsResult += " ";
     }*/
    return wordsResult;
}

bool NumberConverter::isStringNumber(const std::string& stringNumber) {
    std::regex regex_number("(\\d+)");
    if(regex_match(stringNumber, regex_number)) {
        return true;
    } else {
        return false;
    }
}

std::string NumberConverter::convertStringNumberToWords( const std::string& stringNumber ) {
    std::string wordsResult = "";
    std::regex regex_number("(\\d+)");
    
    if(regex_match(stringNumber, regex_number)) {
        int digitsProcessCount = stringNumber.length();
        std::string processNumberStr = stringNumber;
        
        bool allZeros = true;
        for(int iDigit=0; iDigit < stringNumber.length(); ++iDigit) {
            allZeros &= stringNumber[iDigit] == '0';
        }
        if(allZeros == true) {
            wordsResult = numberWord[0];
        } else
        while(digitsProcessCount >= 1) {
            
            int n10partDigitsCount = digitsProcessCount % 3;
            if (n10partDigitsCount == 0) {
                n10partDigitsCount = 3;
            }
            
            std::string degreeN10Part = processNumberStr.substr(0, n10partDigitsCount);
            processNumberStr = stringNumber.substr(n10partDigitsCount, digitsProcessCount);
            
            int processNumber = std::stoi(degreeN10Part);
            
            wordsResult += convertN10Number(processNumber, stringNumber.length() == 1);
            if(digitsProcessCount >= 16 && processNumber != 0) {
                
                int pow1000 = ((digitsProcessCount-1) / 3) * 3;
                wordsResult += " *10^" + std::to_string(pow1000);
                
            } else
            if(digitsProcessCount >= 13 && processNumber != 0) {
                
                wordsResult += " " + num10PowNNames[ TRILLION ];
                
            } else
            if(digitsProcessCount >= 10 && processNumber != 0) {
                
                wordsResult += " " + num10PowNNames[ BILLION ];
                
            } else
            if(digitsProcessCount >= 7 && processNumber != 0) {
                
                wordsResult += " " + num10PowNNames[ MILLION ];
                
            } else
            if(digitsProcessCount >= 4 && processNumber != 0) {
                
                wordsResult += " " + num10PowNNames[ THOUSAND ];
                
            } else
            if(digitsProcessCount >= 1) {
            }
            digitsProcessCount -= n10partDigitsCount;
            
            //Check if all zeros in processNumberStr, we don't need add ','
            if(digitsProcessCount > 0) {
                int max_check_digit = digitsProcessCount > 3 ? 3 : digitsProcessCount;
                bool isNotZero = true;
                for(int iDigit=0; iDigit < max_check_digit; ++iDigit) {
                    isNotZero &= processNumberStr[iDigit] != '0';
                }
                if(isNotZero == true) {
                    wordsResult += ", ";
                }
            }
        }
        
    }
    
    return wordsResult;
}

std::string NumberConverter::convertNumberToWords( long long number ) {
    std::string wordsResult = "";
    std::string word = "";
    
    int digits[16];
    
    long long processNumber = number;
    int digitsNumber = numDigits( int32_t(number) );
    int iDigit = 0;
    number2Digits(digits, number, 16);
    //+2,147,483,647
    iDigit = digitsNumber;
    processNumber = number;
    
    if (iDigit >= 10) {
        processNumber = number % 1000000000000;
        processNumber = processNumber / 1000000000;
        int numDigitsMillion = numDigits(processNumber);
        
        wordsResult += convertN10Number( processNumber ) + " " + num10PowNNames[ BILLION ];
        iDigit -= numDigitsMillion;
        
        processNumber = number % 1000000000;
        if (processNumber > 0) {
            wordsResult += ", ";
        }
    }
    
    if (iDigit >= 7) {
        processNumber = number % 1000000000;
        processNumber = processNumber / 1000000;
        int numDigitsMillion = numDigits(processNumber);
        
        wordsResult += convertN10Number( processNumber ) + " " + num10PowNNames[ MILLION ];
        iDigit -= numDigitsMillion;
        
        processNumber = number % 1000000;
        if (processNumber > 0) {
            wordsResult += ", ";
        }
    }
    
    if (iDigit >= 4) {
        processNumber = number % 1000000;
        processNumber = processNumber / 1000;
        int numDigitsThousand = numDigits(processNumber);
        
        wordsResult += convertN10Number( processNumber ) + " " + num10PowNNames[ THOUSAND ];
        iDigit -= numDigitsThousand;
        
        processNumber = number % 1000;
        if (processNumber > 0) {
            wordsResult += ", ";
        }
    }
    if (iDigit >= 1) {
        processNumber = number % 1000;
        processNumber = processNumber / 1;
        
        wordsResult += convertN10Number( processNumber );
    }
    
    return wordsResult;
}

std::string convertStringNumberToWords(const std::string& number);
