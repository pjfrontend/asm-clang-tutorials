#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

#pragma comment(lib, "winmm.lib")

int main()
{
    // Define message box text and window title
    char WindowText[] = "Press OK to pause playing";
    char ResumeText[] = "Press OK to resume playing new track from paused position";
    char WindowTitle[] = "Micro MIDI Player";

    // Define MCI commands to open and play the first MIDI file
    char OpenCom1[] = "open canon.mid type sequencer alias Music1";
    char PlayCom1[] = "play Music1";

    // Open and play the first MIDI file
    mciSendStringA(OpenCom1, NULL, 0, NULL);
    mciSendStringA(PlayCom1, NULL, 0, NULL);

    // Show a message box to pause the playback
    MessageBoxA(NULL, WindowText, WindowTitle, MB_OK);

    // Pause the current track
    mciSendStringA("pause Music1", NULL, 0, NULL);

    // Get the current position of the paused track
    char Position[128];
    mciSendStringA("status Music1 position", Position, sizeof(Position), NULL);

    // Close the first track
    mciSendStringA("close Music1", NULL, 0, NULL);

    // Define MCI commands to open and play the second MIDI file
    char OpenCom2[] = "open canon-piano.mid type sequencer alias Music2";
    char PlayCom2[128];
    sprintf(PlayCom2, "play Music2 from %s", Position);

    // Open and play the second MIDI file from the paused position
    mciSendStringA(OpenCom2, NULL, 0, NULL);
    // MessageBoxA(NULL, ResumeText, WindowTitle, MB_OK); // Wait for user to resume
    mciSendStringA(PlayCom2, NULL, 0, NULL);

    // Clean up and exit
    MessageBoxA(NULL, "Press OK to exit", WindowTitle, MB_OK);
    mciSendStringA("close Music2", NULL, 0, NULL);
    ExitProcess(0);
    return 0;
}