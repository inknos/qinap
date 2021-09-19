from debian

run apt update 
run apt install -y vim libmagick++-dev
run apt install -y vim graphicsmagick-libmagick-dev-compat

# not working: 
# g++ -std=c++17 `Magick++-config --cxxflags --cppflags` -O2 -Wall `Magick++-config --ldflags --libs` src/main.cpp
g++ -std=c++17 `Magick++-config --cxxflags --cppflags` -O2 -Wall src/main.cpp `Magick++-config --ldflags --libs`


