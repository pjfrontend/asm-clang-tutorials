#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

int main() {
    char WindowText[] = "Press OK to stop playing";
    char WindowTitle[] = "Micro MIDI Player";
    char OpenCom[] = "open canon.mid type sequencer alias Music1";
    char PlayCom[] = "play Music1";

    mciSendStringA(OpenCom, NULL, 0, NULL);
    mciSendStringA(PlayCom, NULL, 0, NULL);
    MessageBoxA(NULL, WindowText, WindowTitle, MB_OK);
    ExitProcess(0);
    return 0;
}