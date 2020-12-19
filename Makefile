CXX := g++
CXXFLAGS := -std=c++11 -Wall -Werror -g
#LDFLAGS := -lGL -lGLU -lglut #Linux flags
LDFLAGS := -framework GLUT -framework OpenGL -framework Cocoa
TARGET := PoisonCookie
VERSION := 1.2

SOURCES := ${wildcard *.cpp}
OBJECTS := ${SOURCES:.cpp=.o}
HEADERS := ${wildcard *.h}

all: $(TARGET)

deb: $(TARGET)
	mkdir -p $(TARGET)_$(VERSION)/usr/local/bin
	cp $(TARGET) $(TARGET)_$(VERSION)/usr/local/bin/.
	mkdir $(TARGET)_$(VERSION)/DEBIAN
	echo "Package: $(TARGET)\n\
Version: $(VERSION)\n\
Section: base\n\
Priority: optional\n\
Architecture: amd64\n\
Depends:\n\
Maintainer: Jared Chapman <jaredpchapman@gmail.com>\n\
Description: PoisonCookie\n\
 Poison Cookie Game\n\
 Try not to eat the poison" > $(TARGET)_$(VERSION)/DEBIAN/control;\
 	dpkg-deb --build $(TARGET)_$(VERSION)
	rm -rf $(TARGET)_$(VERSION)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $< -c

clean:
	-rm -f $(TARGET)
	-rm -f *.o
