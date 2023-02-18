#
#CXX = g++
#CXX = clang++

EXE = engine_demo
IMGUI_DIR = ./imgui/
SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_opengl3.cpp
SOURCES += Camera.cpp rendering/EBO.cpp rendering/Shader.cpp stb.cpp rendering/VAO.cpp rendering/VBO.cpp CubeMap.cpp FpsCounter.cpp GUI.cpp 
SOURCES += rendering/Texture.cpp rendering/Model.cpp rendering/Mesh.cpp rendering/Vertex.cpp 
SOURCES += MainApp.cpp InputHandler.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)


CXXFLAGS = -std=c++17 -I$(IMGUI_DIR) -I./include -DBT_USE_DOUBLE_PRECISION -I/usr/local/include/bullet -I/usr/local/include -I./render/
CXXFLAGS += -g -Wall -Wformat
LIBS = 

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux master race."
	LIBS += -lGL
	LIBS += -lGLEW
	LIBS += `pkg-config --static --libs glfw3`
	LIBS += -lassimp
	LIBS += -L/usr/local/lib -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath
	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X port not implemented."
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "You shouldn't use any microsoft software."
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: render/%.cpp
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
