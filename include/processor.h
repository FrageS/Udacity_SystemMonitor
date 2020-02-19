#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // DONE: See src/processor.cpp
  void SetIdle(int i);
  int GetIdle();
  void SetNonIdle(int i);
  int GetNonIdle();
  // DONE: Declare any necessary private members
 private:
    int prevIdle_ = 0;
    int prevNonIdle_ = 0;
};

#endif