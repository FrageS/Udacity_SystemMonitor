#include <string>

#include "format.h"

using std::string;

// DONE: Complete this helper function
// DONE: Long int measuring seconds
// DONE: HH:MM:SS
// DONE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {     
    int seconds_, minutes, hours;
    minutes = seconds / 60;
    seconds_ = seconds % 60;
    hours = minutes / 60;
    minutes = minutes % 60;
    //Append a 0-digit if time is only 1 digit
    string hours_hh = string(2-std::to_string(hours).size(),'0').append(std::to_string(hours));
    string minutes_mm = string(2-std::to_string(minutes).size(),'0').append(std::to_string(minutes));
    string seconds_ss = string(2-std::to_string(seconds_).size(),'0').append(std::to_string(seconds_));
    string time_ = hours_hh + ":" + minutes_mm + ":" + seconds_ss;
    return time_;     
}