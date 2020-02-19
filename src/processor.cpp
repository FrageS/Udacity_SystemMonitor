#include "processor.h"
#include <string>
using std::string;
#include "linux_parser.h"

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() { 
  string total_proc, key, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  float Idle, NonIdle, Total, CPU_Percentage, total_t, idle_t;
  string line;
  std::ifstream stream("/proc/stat");
  if (stream.is_open()) {    
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);      
      while(linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice) {
        if(key == "cpu") { 
          Idle = strtof(idle.c_str(),0) + strtof(iowait.c_str(),0);           
          NonIdle = strtof(user.c_str(),0) + strtof(nice.c_str(),0) + strtof(system.c_str(),0) +
           strtof(irq.c_str(),0) + strtof(softirq.c_str(),0) + strtof(steal.c_str(),0);
          Total = Idle + NonIdle;
          total_t = Total - GetIdle() - GetNonIdle();
          idle_t = Idle - GetIdle();
          
          CPU_Percentage = (total_t - idle_t)/total_t; 
        }
      } 
    }
  } 
  // Set values for previous state 
  SetIdle(Idle);
  SetNonIdle(NonIdle);
  return CPU_Percentage; 
}

int Processor::GetIdle() {
    return Processor::prevIdle_;
};

int Processor::GetNonIdle() {
    return Processor::prevNonIdle_;
};

void Processor::SetIdle(int i) {
    Processor::prevIdle_ = i;
};

void Processor::SetNonIdle(int i) {
    Processor::prevNonIdle_ = i;
};