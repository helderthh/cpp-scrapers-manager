#include "scraper.hpp"

Scraper::Scraper(const string& name, 
                 Callback callback,
                 ValueRequester request,
                 const int& freq) 
      : m_Name(name), m_Callback(callback), m_Request(request), 
      m_Active(true), m_Frequency(freq) {
  run();
}

Scraper::~Scraper() {
  stop();
}

float Scraper::value() const { return m_Value; }

string Scraper::name() const { return m_Name; }

void Scraper::stop() {
  m_Active = false;

  if (!m_Thread->joinable())
    return;

  cout << "Stopping scrapper " << m_Name << endl;
  m_Thread->join();
  cout << "Scrapper " << m_Name << " stopped" << endl;
}

void Scraper::run() {
  if (m_Thread)
    return;

  m_Thread = new thread([this]{
    while (m_Active) {
      m_Value = m_Request();

      if (m_Active) 
        m_Callback(m_Name, m_Value);
      
      this_thread::sleep_for(chrono::seconds(m_Frequency));
    }
  });
}
