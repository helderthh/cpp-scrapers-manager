CXX = clang++
CXXFLAGS += -std=c++2a

LDFLAGS += -lcurl

INCLUDE_PATH = include
SRC_PATH = src

CPPFLAGS += -I$(INCLUDE_PATH)


all: crypto-scraper
	./crypto-scraper

crypto-scraper: $(INCLUDE_PATH)/scraper.o $(INCLUDE_PATH)/manager.o
	$(CXX) $(CXXFLAGS) -o $@ $^ main.cpp $(CPPFLAGS) $(LDFLAGS)

$(INCLUDE_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -I$(INCLUDE_PATH) -c -o $@ $<

clear:
	rm crypto-scraper $(INCLUDE_PATH)/*.o
