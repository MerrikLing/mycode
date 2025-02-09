//#include<cstdio>
//#include <windows.h>
//
//int main() 
//{
//    while (1)
//    {
//        Sleep(70);
//        if (GetAsyncKeyState(VK_A) & 0x8000)
//        {
//            printf("a is pressed");
//            while(GetAsyncKeyState('a') & 0x8000)
//            {
//                Sleep(50);
//            }
//            printf("a is released");
//            break;
//        }
//    }
//
//    return 0;
//}

#include <cstdio>
#include <windows.h>

int main() {
    while (1) {
        Sleep(70);
        if (GetAsyncKeyState('a') & 0x8000) {
            while (GetAsyncKeyState('a') & 0x8000) {
                Sleep(50);
            }
            printf("a is pressed\n");
            break;
        }
    }

    return 0;
}