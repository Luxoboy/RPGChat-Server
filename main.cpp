/* 
 * File:   main.cpp
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:09
 */

#include <cstdlib>

#include "Server.h"
#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    Server s1;
    if(s1.ready())
        s1.accept();
    
    return 0;
}

