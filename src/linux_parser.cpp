#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <experimental/filesystem>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
namespace fs = std::experimental::filesystem;
// ------------------------------------- DONE --------------------------------------------------//
// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime_;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime_;
  }
  
  long time_ = atol(uptime_.c_str());

  return time_;   
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  /*for(auto& p : fs::directory_iterator(kProcDirectory))
  {
    if(fs::is_directory(p.path()) == 1)
    {
      std::string pid_id = p.path().filename().string();
      if(std::all_of(pid_id.begin(), pid_id.end(), isdigit))
      {
        int pid = stoi(pid_id);
        pids.push_back(pid);
      }
    }
  }*/
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  
  string mem_total, mem_free, key, value;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      //std::cout << line << "\n";
      while(linestream >> key >> value) {
        if(key == "MemTotal:") {          
          mem_total = value;          
        }
        if(key == "MemFree:") {          
          mem_free = value;          
        }
      } 
    }
  }

  return 1 - strtof(mem_free.c_str(),0) / strtof(mem_total.c_str(),0);
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {   
  string running_proc, key;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {    
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);      
      while(linestream >> key >> running_proc) {
        if(key == "procs_running") {          
          return stoi(running_proc);          
        }
      } 
    }
  }
  return stoi(running_proc);   
}

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string total_proc, key;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {    
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);      
      while(linestream >> key >> total_proc) {
        if(key == "processes") {          
          return stoi(total_proc);          
        }
      } 
    }
  }
  return stoi(total_proc); 
}


vector<string> LinuxParser::CpuUtilization() { 
  string key, line;
  vector<string> cpu_util;   
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {    
    std::getline(stream, line);
    std::istringstream linestream(line);         
    while(linestream >> key) {
      if(key != "cpu") { 
        cpu_util.push_back(key);
      }
    }
  }
  return cpu_util; 
}
// ------------------------------------- DONE - PROCESSES --------------------------------------------------//
// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string user, uid, x;
  string line;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {    
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);      
      while(linestream >> user >> x >> uid) {
        if(uid == Uid(pid)) {          
          return user;                   
        }
      } 
    }
  }
  return user; 
}

string LinuxParser::Uid(int pid) { 
  string UID, key;
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (stream.is_open()) {    
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);      
      while(linestream >> key >> UID) {
        if(key == "Uid:") {          
          return UID;          
        }
      } 
    }
  }
  return UID;
}

// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  string uptime_, line;  
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int id = 0;
    while(linestream >> uptime_)
    {
      if(id==21)
        return stol(uptime_) / sysconf(_SC_CLK_TCK);
      id++;
    }    
  } 
  return 0;
}

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string command, key;  
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {    
    std::getline(stream, command);    
  }
  return command;  
}

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string line, key; 
  int mem; 
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);  
  if (stream.is_open()) {    
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);      
      while(linestream >> key >> mem) {
        if(key == "VmHWM:") { // same as HTOP is using for RES memory, instead of the virtual memory         
          mem = mem*0.001;
          return to_string(mem);          
        }
      } 
    }
  }  
  return to_string(mem);
}

// DONE: Read and return Process utilization
vector<string> LinuxParser::PidUtilization(int pid) { 
  string line, key; 
  vector<string> pid_util; 
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);  
  if (stream.is_open()) {    
    std::getline(stream, line) ;
    std::istringstream linestream(line);        
    int i = 0;
    while(linestream >> key) {
      if(i == 13 || i == 14 || i == 15 || i == 16 || i == 21) {          
        pid_util.push_back(key);                
      }
      i++;
    }     
  }  
  return pid_util; 
}


// ------------------------------------- TODO --------------------------------------------------//
/* WHY?
// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }*/

