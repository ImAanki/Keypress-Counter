// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

class Engine {
    public:
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        bool Status = false;
        std::string StatusMessages[2] = {"Offline", "Online"};
        int KeyArray[10] = {};
        int StatusColours[2] = { 4, 2 };
        int KeyPressCount = 0;
        void Start();
        void Stop();
        void Update();
        void ConsoleClear();
        void Increment();
        bool GetState();
};

void Engine::ConsoleClear() {
    COORD topLeft = { 0, 0 };
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO screen;
    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

void Engine::Increment() {
    KeyPressCount = KeyPressCount + 1;
}

bool Engine::GetState() {
    return Status;
}

void Engine::Update() {
    Engine::ConsoleClear();
    SetConsoleTextAttribute(console, 15);
    std::cout << "Aanki's Key Tracker Tool\nCurrent Status: ";
    SetConsoleTextAttribute(console, StatusColours[Status]);
    std::cout << StatusMessages[Status];
    SetConsoleTextAttribute(console, 15);
    std::cout << "\nCurrent Count: " << KeyPressCount;

};

void Engine::Start() {
    Status = true;
};

void Engine::Stop() {
    Status = false;
};


bool HasFocus()
{
    return(GetFocus() == GetConsoleWindow());
}

int main()
{
    clock_t Time = clock();
    Engine GameEngine = Engine();
    bool EnableSwitch = false;
    bool wasDown = false;
    std::string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    GameEngine.Update();

    while (true) {
        for (char C : Alphabet) {
            if (GetKeyState(C) & 0x8000) {
                if (!GameEngine.KeyArray[C] && GameEngine.Status) {
                    GameEngine.Increment();
                    GameEngine.KeyArray[C] = true;
                }
            }
            else {
                GameEngine.KeyArray[C] = false;
            }
        }

        if (GetKeyState(VK_F8) & 0x8000) {
            if (!wasDown) {
                wasDown = true;
                if (!GameEngine.Status) {
                    GameEngine.Start();
                }
                else {
                    GameEngine.Stop();
                }

                GameEngine.Update();
            }
        }
        else {
            wasDown = false;
        };

        //if (_kbhit() && GameEngine.Status) {
        //    GameEngine.Increment();
        //}
        
        if (clock() - Time >= 2500) {
            Time = clock();
            GameEngine.Update();
        }
        Sleep(1);
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
