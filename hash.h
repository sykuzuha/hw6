#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
//#include <iostream>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::string str = k;
        for (std::string::size_type i=0; i<k.length(); ++i)
        {
            str[i] = std::tolower(k[i]);
        }
        unsigned long long w[5] = {0,0,0,0,0};
        int stringIndex = str.length() - 1;
        int wIndex = 4;
        int power[] = {1, 36, 1296, 46656, 1679616, 60466176};
        int powerIndex = 0;
        while((stringIndex >= 0) && (wIndex >= 0))
        {
            w[wIndex] += (power[powerIndex]*letterDigitToNumber(str[stringIndex]));
            stringIndex-=1;
            powerIndex+=1;
            if(powerIndex > 5)
            {
              powerIndex = 0;
              wIndex-=1;
            }
            //std::cout << "stringIndex: " << stringIndex << std::endl;
        


        }
        HASH_INDEX_T result = 0;
        for(int i = 0; i <= 4; i++)
        {
            //std::cout << "w[" << i << "] = " << w[i] << std::endl;
            result += rValues[i]*w[i];

        }
        return result;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T num;
        if((letter >= 48) && (letter <= 57))
        {
          //0 is 48 in ASCII, 9 is 57 in ASCII
          num = letter - 22;
        }
        else
        {
          //a is 97 in ASCII
          num = letter - 97;
        }
        //std::cout << letter << " turns to: " << num << std::endl;
        return num;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
