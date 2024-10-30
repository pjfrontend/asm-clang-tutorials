#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

std::string format_time(float seconds)
{
    int hours = static_cast<int>(seconds / 3600);
    seconds = std::fmod(seconds, 3600);
    int minutes = static_cast<int>(seconds / 60);
    seconds = std::fmod(seconds, 60);
    int wholeSeconds = static_cast<int>(seconds);
    int milliseconds = static_cast<int>((seconds - wholeSeconds) * 100);

    std::ostringstream oss;

    // Format the time with leading zeros
    oss << std::setw(3) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << wholeSeconds << "."
        << std::setw(2) << std::setfill('0') << milliseconds;

    return oss.str();
}

int main()
{
    float inputSeconds = 3661.789;
    std::string formattedTime = format_time(inputSeconds);
    // OUTCOME: Formatted time: 001:01:01.78
    std::cout << "Formatted time: " << formattedTime << std::endl;
    return 0;
}
