#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// ------------------------------------- DONE --------------------------------------------------//
// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() {
    string const& os_kernel = LinuxParser::Kernel();
    return os_kernel; 
}

// DONE: Return the operating system name
std::string System::OperatingSystem() { 
    string const& os_string = LinuxParser::OperatingSystem();    
    return os_string;     
}

// DONE: Return the number of seconds since the system started running
long int System::UpTime() { 
    long const& time_ = LinuxParser::UpTime();
    
    return time_; 
}

// DONE: Return the system's memory utilization
float System::MemoryUtilization() { 
    float const& mem_util = LinuxParser::MemoryUtilization();
    return mem_util;     
}

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    int const& running_proc = LinuxParser::RunningProcesses();
    return running_proc; 
}

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { 
    int const& total_proc = LinuxParser::TotalProcesses();
    return total_proc; 
}

// DONE: Return the system's CPU
Processor& System::Cpu() { return cpu_; }
// ------------------------------------- TODO --------------------------------------------------//



// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }



