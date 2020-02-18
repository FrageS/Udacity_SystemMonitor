#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// DONE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int seconds_, minutes, hours;
    minutes = seconds / 60;
    seconds_ = seconds % 60;
    hours = minutes / 60;
    minutes = minutes % 60;
    string time_ = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds_);
    return time_; 
    
}