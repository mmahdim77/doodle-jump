#OBJS specifies which files to compile as part of the project 
OBJS = doodle.cpp #OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = program #This is the target that compiles our executable 
all : $(OBJS) 
	g++ $(OBJS) -w -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lSDL2_gfx  -o $(OBJ_NAME)