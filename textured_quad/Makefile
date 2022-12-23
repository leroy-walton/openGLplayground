
#CXX = g++

EXE = textured_quad

SOURCES = main.cpp
SOURCES += VAO.cpp VBO.cpp EBO.cpp Shader.cpp Texture.cpp

#IMGUI_DIR = ./imgui/
#SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
#SOURCES += $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_opengl3.cpp
#SOURCES += Camera.cpp EBO.cpp Shader.cpp stb.cpp VAO.cpp VBO.cpp CubeMap.cpp FpsCounter.cpp GUI.cpp Texture.cpp ModelLoader.cpp Model.cpp Mesh.cpp Vertex.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

CXXFLAGS = -g -Wall -Wformat -std=c++11 -I./include
#CXXFLAGS += -I$(IMGUI_DIR)


ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL -lGLEW -lglfw
	CXXFLAGS += 
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "You shouldn't use any microsoft softwares."
endif

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
