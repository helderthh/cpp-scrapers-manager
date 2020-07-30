#ifndef SCRAPER_H
#define SCRAPER_H

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std;


using Callback = function<void(const string&, const float)>;
using ValueRequester = function<float()>;

class Scraper {
  static constexpr int DEFAULT_FREQUENCY_IN_SECS = 3;

public:
  Scraper(const string& name, 
          Callback callback,
          ValueRequester request,
          const int& freq=DEFAULT_FREQUENCY_IN_SECS);
  ~Scraper();

  float value() const;
  string name() const;
  void stop();

protected:
  void run();
  
private:
  const Callback m_Callback;
  const ValueRequester m_Request;
  const string m_Name;
  float m_Value;
  const int m_Frequency;
  bool m_Active;
  thread* m_Thread;
};

#endif