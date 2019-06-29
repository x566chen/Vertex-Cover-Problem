#include<iostream>
#include <stdlib.h>
#include "stdio.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <unistd.h>

int funky(int x)
{
    if (x>0){
        x -=1;
        funky(x);
    }

    printf("%d",x);
}

int main()
{
    funky(5);
    return 0;
}
