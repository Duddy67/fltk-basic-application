SRC = main.cpp application/menu.cpp application/callbacks.cpp dialogs/dialog.cpp \
      dialogs/new.cpp application/menu/edit.cpp
CXX = g++
CXXFLAGS = -Wall $(shell fltk-config --cxxflags)

LFLAGS = $(shell fltk-config --ldflags)

OBJS = $(SRC:.cpp=.o)
DIR_OBJ = obj/
DIR_OBJS = $(addprefix $(DIR_OBJ), $(OBJS))

$(DIR_OBJ)%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) -c $(<) -o $(@)

EXE = basicApplication

all: $(EXE)

$(EXE): $(DIR_OBJS)
	$(CXX) -o $@ $^ $(LFLAGS)

depend:
	makedepend -- $(CXXFLAGS) -- $(SRC)

strip: $(EXE)
	strip --strip-all $(EXE)

clean:
	rm -f $(DIR_OBJS)
	rm -f $(EXE)
