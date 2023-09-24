// C++ code to determine whether the machine is little or big endian.  
#include <iostream>  
int main ()  
{  
unsigned int num = 1;  
char *c = (char*) & num;  
  
if (*c)  
    std::cout << "THE MACHINE IS LITTLE ENDIAN";  
else  
    std::cout << "THE MACHINE IS BIG ENDIAN";  
  
return 0;  
}  
