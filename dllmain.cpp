// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef long long LL;

static bool getflag(LL base,int h,int w)
{
    LL temp2 = base;
    if (temp2 + 0x18)
    {
        temp2 = *(LL*)(temp2 + 0x18);
        if (temp2 + 0x58)
        {
            temp2 = *(LL*)(temp2 + 0x58);
            if (temp2 + 0x10)
            {
                temp2 = *(LL*)(temp2 + 0x10);
                if (temp2 + w * 8)
                {
                    temp2 = *(LL*)(temp2 + w * 8);
                    if (temp2 + 0x10)
                    {
                        temp2 = *(LL*)(temp2 + 0x10);
                        if((BYTE*)temp2 + h)
                            return *((BYTE*)temp2 + h);
                    }
                }
            }
        }
        
    }
    return 0;
}

static void PrintMap()
{
    HMODULE exe = GetModuleHandleA("Minesweeper.exe");
    //char str[256] = { 0 };
    //sprintf(str, "%p", exe);
    //MessageBoxA(0, str, "Hi", MB_ICONINFORMATION);
    if (exe)
    {
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        while (1)
        {

            int w;
            int h;
            LL base = *(LL*)((LL)exe + 0xAAA38);
            LL temp1 = base;
            temp1 = *(LL*)(temp1 + 0x10);
            temp1 = *(LL*)(temp1 + 0x38);
            int*   BombMax   = (int*)  (temp1 + 0x8);
            int*   HeightMax = (int*)  (temp1 + 0xC);
            int*   Widthmax  = (int*)  (temp1 + 0x10);
            int*   FlagCount = (int*)  (temp1 + 0x14);
            int*   FlipCount = (int*)  (temp1 + 0x18);
            int*   StepCount = (int*)  (temp1 + 0x1C);
            float* Time      = (float*)(temp1 + 0x20);
            if (*StepCount)
            {
                *Time = 0;
                for (h = 0; h < *HeightMax; ++h)
                {

                    for (w = 0; w < *Widthmax; ++w)
                    {
                        bool flag = getflag(base, h, w);
                        if (flag)
                        {
                            printf("X ");
                        }
                        else
                        {
                            int count = 0;
                            count += getflag(base, h, w);
                            if (h + 1 < *HeightMax)
                                count += getflag(base, h + 1, w);
                            if (h - 1 >= 0)
                                count += getflag(base, h - 1, w);
                            if (w + 1 < *Widthmax)
                                count += getflag(base, h, w + 1);
                            if (w - 1 >= 0)
                                count += getflag(base, h, w - 1);
                            if (h + 1 < *HeightMax && w + 1 < *Widthmax)
                                count += getflag(base, h + 1, w + 1);
                            if (h + 1 < *HeightMax && w - 1 >= 0)
                                count += getflag(base, h + 1, w - 1);
                            if (h - 1 >= 0 && w + 1 < *Widthmax)
                                count += getflag(base, h - 1, w + 1);
                            if (h - 1 >= 0 && w - 1 >= 0)
                                count += getflag(base, h - 1, w - 1);
                            char str[20] = {};
                            if (count)
                            {
                                sprintf(str, "%d ", count);
                            }
                            else
                            {
                                sprintf(str, "  ");
                            }
                            printf(str);
                        }

                    }
                    printf("\n");
                }
                printf("\n");
            }
            else
            {
                printf("游戏未开始！\n");
            }
            system("pause");
            system("cls");
        }
        FreeConsole();
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PrintMap, 0, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
