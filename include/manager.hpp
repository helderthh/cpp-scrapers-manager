#ifndef SCRAPER_MANAGER_H
#define SCRAPER_MANAGER_H

#include <mutex>
#include <string>
#include <chrono>

#include "scraper.hpp"

class ScrapersManager {
public:
  ScrapersManager();

  void addScraper(const shared_ptr<Scraper> &s);

  void addScraper(
      const string& name, 
      ValueRequester request,
      const int& freq);

  void stopAll();

protected:
  void callback(const string& name, const float value);


  mutex m_Mutex;
  chrono::system_clock::time_point m_LastUpdate;  // last update shown to the client
  vector<shared_ptr<Scraper>> m_Scrapers;
};

#endif