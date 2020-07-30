#include "manager.hpp"

ScrapersManager::ScrapersManager() {
  m_LastUpdate = chrono::system_clock::now();
}

void ScrapersManager::addScraper(const shared_ptr<Scraper> &s) {
m_Scrapers.push_back(s);
}

void ScrapersManager::addScraper(
  const string& name, 
  ValueRequester request,
  const int& freq) {
  Callback callback = [this] (const string& name, const float value) {
    this->callback(name, value);
  };

  m_Scrapers.push_back(make_shared<Scraper>(
    name, callback, request, freq));
}

void ScrapersManager::stopAll() {
  for (const shared_ptr<Scraper> &s: m_Scrapers)
    s->stop();
}

void ScrapersManager::callback(const string& name, const float value) {
  lock_guard<mutex> guard(m_Mutex);
  
  auto diff = chrono::duration<double>(chrono::system_clock::now() - m_LastUpdate);
  if (diff > chrono::seconds(5)) {
    m_LastUpdate = chrono::system_clock::now();

    for (const shared_ptr<Scraper> &s: m_Scrapers)
      cout << s->name() <<": " << s->value() << endl;
      
    cout << endl <<endl;
  }
}
