#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
    pid_ = pid;
    user_ = LinuxParser::User(pid_);
    uptime_ = LinuxParser::UpTime(pid_);
    command_ = LinuxParser::Command(pid_);
    ram_ = LinuxParser::Ram(pid_);
    cpu_usage_ = CpuUtilizationCalc(pid_);

}

// DONE: Return this process's ID
int Process::Pid() { return pid_; }

// DONE: Return the user (name) that generated this process
string Process::User() { return user_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// DONE: Return the command that generated this process
string Process::Command() { return command_; }

// DONE: Return this process's memory utilization
string Process::Ram() { return ram_; }

float Process::CpuUtilizationCalc(int pid) {
    long uptime = LinuxParser::UpTime();
    std::vector<string> process_state = LinuxParser::PidUtilization(pid);
  
    long total_time = stol(process_state[0]) + stol(process_state[1]);  
    total_time += stol(process_state[2]) + stol(process_state[3]);  
    float seconds = uptime - (stol(process_state[4]) / sysconf(_SC_CLK_TCK));
    cpu_usage_ = ((total_time / sysconf(_SC_CLK_TCK)) / seconds);
    return cpu_usage_;
}   

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_usage_; }

// DONE: Overload the "less than" comparison operator for Process objects/
bool Process::operator<(Process const& a) const { 
    if (a.cpu_usage_ < cpu_usage_)
    {
        return true;
    }        
    else
    {
        return false;
    }
    
    return true; }