#include <iostream>
#include <string>

#include "manager.hpp"
#include "request.hpp"

using namespace std;


const string BTC_COINMARKETCAP = "<a href=\"/currencies/bitcoin/markets/\" class=\"cmc-link\">$";
const string ETH_COINMARKETCAP = "<a href=\"/currencies/ethereum/markets/\" class=\"cmc-link\">$";
const string USDT_COINMARKETCAP = "<a href=\"/currencies/tether/markets/\" class=\"cmc-link\">$";


float scrapCoinMarketCap(const string& target) {
  string data;
  SimpleRequest("https://www.coinmarketcap.com/", data);

  size_t beg = data.find(target) + target.length();
  size_t end = data.find("<", beg);

  string sValue = data.substr(beg, end - beg);

  sValue.erase(remove(sValue.begin(), sValue.end(), ','), sValue.end());

  return stof(sValue);
}


int main() {
  cout << endl
       << "Welcome! You will see the value of some "
       << "cryptocurrencies each 5 seconds." << endl << endl;
  
  curl_global_init(CURL_GLOBAL_ALL);

  ScrapersManager manager;
  manager.addScraper("BTC", []{ return scrapCoinMarketCap(BTC_COINMARKETCAP); }, 2);
  manager.addScraper("ETH", []{ return scrapCoinMarketCap(ETH_COINMARKETCAP); }, 3);
  manager.addScraper("Tether", [] { return scrapCoinMarketCap(USDT_COINMARKETCAP); }, 3);

  this_thread::sleep_for(chrono::seconds(3));

  cout << "* Press ENTER to stop the scrapers *" << endl << endl;

  if(cin.get())
    std::cout << "Alright..."<< '\n';

  manager.stopAll();
  
  curl_global_cleanup();
  return 0;
}
