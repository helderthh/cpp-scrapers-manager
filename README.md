# Crypto-Scrapers

This C++ program is intended to be a small guide or example to build a simple scrapers manager using cURL to make requests. If you are looking for a simple C++ example, threads and requests then you are in the right place.

You will find 2 basic entities and some utilities which are described below.

## Main entities

### Scraper class

This is the base entity of this program. A `Scraper` creates a thread as soon as it is built, and such thread will execute a `request` using a given requester method with some given `frequency`. 

Everytime a request is made its response (the value of a cryptocurrency i.e.) will be sent to the given `callback` method. The scrapers can be stopped calling `stop()`.

### ScrapersManager class

The main entity is `ScrapersManager`, an instance of this class will control scrapers which are added using `addScraper()` and at the end of the execution you should always call `stopAll()`.


## Utilities

### Aliases

Scrapers expect a callback and a requester method, which should have the following "type":

```cpp
using Callback = function<void(const string&, const float)>;
using ValueRequester = function<float()>;
```

### SimpleRequest class

This is a simplified method to make GET requests using cURL, just pass the URL and a `string` which will be used as a buffer to save the response.


## Example

In main.cpp you will find an example for scraping `coinmarketcap.com` using the `SimpleRequester` and looking for the prices of Bitcoin, Ethereum y Tether with a `Scraper` for each one of them.


Output:
```
Welcome! You will see the value of some cryptocurrencies each 5 seconds.

* Press ENTER to stop the scrapers *

BTC: 10890.8
ETH: 315.53
Tether: 1
```

The prices will be printed each 5 seconds, but every scraper will request/update its value with the specified frequencies.

### Running the example

You will find a Makefile so just use `make run`.

That's it, give it a look :D