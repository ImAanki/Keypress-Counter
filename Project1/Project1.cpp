// FIRST C++ PROGRAM
//
// PUSH TEST

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>

class Brain {
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

void Brain::ConsoleClear() {
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

void Brain::Increment() {
    KeyPressCount = KeyPressCount + 1;
}

bool Brain::GetState() {
    return Status;
}

void Brain::Update() {
    Brain::ConsoleClear();
    SetConsoleTextAttribute(console, 15);
    std::cout << "Aanki's Key Tracker Tool\nCurrent Status: ";
    SetConsoleTextAttribute(console, StatusColours[Status]);
    std::cout << StatusMessages[Status];
    SetConsoleTextAttribute(console, 15);
    std::cout << "\nCurrent Count: " << KeyPressCount;

};

void Brain::Start() {
    Status = true;
};

void Brain::Stop() {
    Status = false;
};


bool HasFocus()
{
    return(GetFocus() == GetConsoleWindow());
}

int main()
{
    clock_t Time = clock();
    Brain BrainHandler = Brain();
    bool EnableSwitch = false;
    bool wasDown = false;
    std::string Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    BrainHandler.Update();

    while (true) {
        for (char C : Alphabet) {
            if (GetKeyState(C) & 0x8000) {
                if (!BrainHandler.KeyArray[C] && BrainHandler.Status) {
                    BrainHandler.Increment();
                    BrainHandler.KeyArray[C] = true;
                }
            }
            else {
                BrainHandler.KeyArray[C] = false;
            }
        }

        if (GetKeyState(VK_F8) & 0x8000) {
            if (!wasDown) {
                wasDown = true;
                if (!BrainHandler.Status) {
                    BrainHandler.Start();
                }
                else {
                    BrainHandler.Stop();
                }

                BrainHandler.Update();
            }
        }
        else {
            wasDown = false;
        };
        
        if (clock() - Time >= 2500) {
            Time = clock();
            BrainHandler.Update();
        }
        Sleep(1);
    }

    return 0;
}