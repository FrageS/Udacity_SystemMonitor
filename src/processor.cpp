#include "processor.h"
#include <string>
using std::string;
#include "linux_parser.h"
using LinuxParser::CPUStates;

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {   
  std::vector<std::string> cpu_util = LinuxParser::CpuUtilization();
  float Idle, NonIdle, Total, CPU_Percentage, total_t, idle_t;  
  Idle = strtof(cpu_util[CPUStates::kIdle_].c_str(),0) + strtof(cpu_util[CPUStates::kIOwait_].c_str(),0);
  NonIdle = strtof(cpu_util[CPUStates::kUser_].c_str(),0) + strtof(cpu_util[CPUStates::kNice_].c_str(),0) + strtof(cpu_util[CPUStates::kSystem_].c_str(),0) +
           strtof(cpu_util[CPUStates::kIRQ_].c_str(),0) + strtof(cpu_util[CPUStates::kSoftIRQ_].c_str(),0) + strtof(cpu_util[CPUStates::kSteal_].c_str(),0); 
  Total = Idle + NonIdle; 
  total_t = Total - GetIdle() - GetNonIdle();
  idle_t = Idle - GetIdle();          
  CPU_Percentage = (total_t - idle_t)/total_t; 

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