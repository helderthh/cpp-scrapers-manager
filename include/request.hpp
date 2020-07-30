#ifndef SIMPLE_REQUEST_MANAGER_H
#define SIMPLE_REQUEST_MANAGER_H

#include <string>
#include <curl/curl.h> //your directory may be different

class SimpleRequest {
public:
  SimpleRequest(const string &url, string &data) {
    m_Conn = curl_easy_init();

    curl_easy_setopt(m_Conn, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_Conn, CURLOPT_WRITEFUNCTION, writeFromCURL);
    curl_easy_setopt(m_Conn, CURLOPT_WRITEDATA, &data);

    curl_easy_perform(m_Conn);
  }

  ~SimpleRequest() {
    curl_easy_cleanup(m_Conn);
  }
  

protected:
  static size_t writeFromCURL(char* buf, size_t size, size_t nmemb, string* up) { 
    if(up == NULL)
      return 0;

    up->append(buf, size*nmemb);

    return size*nmemb;
  }

  CURL* m_Conn;
};

#endif