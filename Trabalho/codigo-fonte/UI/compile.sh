
g++  `pkg-config --libs gtk+-3.0` ui_teste.cpp -llept -ltesseract -rdynamic -o ui -export-dynamic  -Wno-format `pkg-config gtk+-3.0 --cflags --libs opencv3`  

#g++ opencvex.cpp -o oc -llept -ltesseract `pkg-config --cflags --libs opencv4`
