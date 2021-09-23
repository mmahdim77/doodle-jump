//============================================================================
// Name        : doodle.cpp
// Author      : M.Mahdi.Maghouli
// Version     : 1.0
// Copyright   : 
// Description : doodle jump program by SDL graphical library
//============================================================================

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "hash.h"
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
#define PATH ""
using namespace std;

/**************** Enum Defintion *****************/

enum GameScreen {
  
    MainMenue,
    playGround,
    score,
    options,
    GameOver
};
enum ObjectMouseStatus
{
	Nothing,
	OnIt,
	Clicked
};
enum ObjectType{
    GreenBlock,
    BlueBlock,
    GrayBlock,
    FakeBlock,
    FakeBlock0,
    whiteBlock,
    DarkBlock,
    TimerYtoLBlock

};


/******************* Structs ********************/

struct position {
    float x;
    float y;
};

struct objects{
    position pos;
    int width;
    int height;    
    ObjectType Type;
    bool life=false;
};
struct Blucks{
    position pos;
    short int width;
    short int height;    
    ObjectType Type;
    bool life=false;
    bool moveFlag=false;
    short int blCounter;
};
struct MenuItem
{
	position Pos;
	ObjectMouseStatus MouseStatus;
};
struct Scores
{
    bool enable=false;
    int points;
};


/**************** Global Variable Defintion *****************/

/**  Main surface **/
SDL_Surface* screen;
SDL_Surface* back_ground;
GameScreen currScreen;	
//**  Surface for images **//
//doodler
SDL_Surface* doodler_temp;

SDL_Surface* doodler_right;

SDL_Surface* doodler_left;

SDL_Surface* doodler_up;

SDL_Surface* doodler_nose;
//blocks
SDL_Surface* green_block;
SDL_Surface* blue_block;

SDL_Surface* fake_blockf1;
SDL_Surface* fake_blockf0;
SDL_Surface* fake_blockf2;
SDL_Surface* fake_blockf3;
SDL_Surface* fake_blockf4;

SDL_Surface* Gray_block;
SDL_Surface* white_block;


SDL_Surface* YtoR_block;
//enemy
SDL_Surface* monster1f1;
SDL_Surface* monster1f2;
SDL_Surface* monster1f3;
SDL_Surface* monster1f4;

SDL_Surface* monster2f1;
SDL_Surface* monster2f2;

SDL_Surface* monster3;

SDL_Surface* monster4;

SDL_Surface* monster5f1;
SDL_Surface* monster5f2;
SDL_Surface* monster5f3;
SDL_Surface* monster5f4;
SDL_Surface* monster5f5;

SDL_Surface* monster6;

SDL_Surface* black_hole;

SDL_Surface* UFOf1;
SDL_Surface* UFOf2;

//springers
SDL_Surface* springf1;
SDL_Surface* springf2;

SDL_Surface* spring_shoesf1;
SDL_Surface* spring_shoesf2;
SDL_Surface* spring_shoesf3;
SDL_Surface* spring_shoesf4;
SDL_Surface* spring_shoesf5;

SDL_Surface* trampolinef1;
SDL_Surface* trampolinef2;
SDL_Surface* trampolinef3;

//flyer
SDL_Surface* jetpackf1;
SDL_Surface* jetpackf2;
SDL_Surface* jetpackf3;
SDL_Surface* jetpackf4;
SDL_Surface* jetpackf5;
SDL_Surface* jetpackf6;
SDL_Surface* jetpackf7;
SDL_Surface* jetpackf8;
SDL_Surface* jetpackf9;
SDL_Surface* jetpackf10;

SDL_Surface* propeller;

SDL_Surface* capf1;
SDL_Surface* capf2;
SDL_Surface* capf3;
SDL_Surface* capf4;

//shield
SDL_Surface* shield;
SDL_Surface* shieldf1;
SDL_Surface* shieldf2;
SDL_Surface* shieldf3;

//butts
SDL_Surface* play;
SDL_Surface* playon;
SDL_Surface* loading;
SDL_Surface* menu;
SDL_Surface* menuon;
SDL_Surface* option;
SDL_Surface* optionon;
SDL_Surface* playagain;
SDL_Surface* playagainon;
SDL_Surface* resume;
SDL_Surface* scores;
SDL_Surface* scoreson;


//	TTF fonts

TTF_Font* bhoma;
TTF_Font* Doodlejump80;
TTF_Font* Doodlejump70;
TTF_Font* Doodlejump60;
TTF_Font* Doodlejump50;
TTF_Font* Doodlejump30;
TTF_Font* Doodlejump20;


//  sounds
Sound* jump;
Sound* feder;
Sound* jetpack;
Sound* fakeblock;
Sound* monsterblizu;
Sound* propeller5;
Sound* springshoes;
Sound* trampoline;
Sound* ufo;
Sound* basic_throw;
Sound* fall;
bool sound_flag=true;

GameScreen currentsc=MainMenue;

const int screen_height = 1024;
const int screen_width = 640;
bool basegamescreen=true;

//main menu objects
SDL_Surface* doodle_jump;
objects doodlermain;
Blucks bl_green_menu;
float a,x,t,x0,v,jump_time,jump_length;
MenuItem playItem;
MenuItem optionsItem;
MenuItem scoresItem;
MenuItem onItem;
MenuItem offItem;
MenuItem menuItem;
MenuItem scoremenuItem;
MenuItem PAmenuItem;


//options
SDL_Surface* op_sounds;
SDL_Surface* op_sounds_on_gray;
SDL_Surface* op_sounds_on_green;
SDL_Surface* op_sounds_off_gray;
SDL_Surface* op_sounds_off_green;

//scores
int HighScore;
vector <int> playerScore(10);
int score_temp;

//Game objects
float   doodler_a, 
        doodler_t,
        doodler_v,
        doodler_x0,
        doodler_jump_time, 
        doodler_jump_length, 
        doodler_v0,
        doodler_vbar;
int scrolDown=0;
objects doodler;
objects shieldObject;
objects blackhole;
objects monsters;
vector <Blucks> bluck(40);
Blucks bluck_temp;
Blucks tempo;
int xplace=screen_height-100;
int type;
int cheker=0;
int bl_t=0;
int block_v;
int block_scrol_y;
int point = 0;
int shield_time = 10;
int temp;
short int ii=0;
char Point[10];
SDL_Surface* bar;
SDL_Surface* insect1;
SDL_Surface* insect2;
SDL_Surface* insect3;
short int gameplay=0;

SDL_Surface* nose ,*lik;
SDL_Surface* rotated;
//vector <objects> bl_green(10,0);


/**************** Function Defintion *****************/
void LoadResources();
void LoadImages();
void LoadAudioes();
void LoadFonts();
void mainmenuevariables();
inline bool IsMouseOnPlayItem();
inline bool IsMouseOnOptions();
inline bool IsMouseOnScores();
inline bool IsMouseOnOn();
inline bool IsMouseOnOff();
inline bool IsMouseOnmenu();
inline void DrawMainMenue ();
inline void menulogic();
inline void menudoodleLogic();
inline void DrawOptionsMenue ();
void doodlerVariables();
void doodlerLogic();
void DrawDoodler();
void shieldLogic();
void DrawGameOver ();
void scoresLogic();


void blucksLogic ();


int main() 
{

	/***************** Loading Section **********************/
	InitEngine(screen,"Doodle Jump",screen_width,screen_height);
	LoadResources();
    mainmenuevariables();
    doodlerVariables();
    doodler_temp=doodler_right;
	/**************** Initializing Section *****************/

	while(!ExitRequested)
	{
		Update();
	    SDL_BlitSurface(back_ground,screen,0,0);

        switch (currScreen) {
            case MainMenue :
                DrawMainMenue();
                break;
            case options :
                DrawOptionsMenue();
                break;
            case playGround :
                blucksLogic();
                DrawDoodler ();
                break;
            case GameOver:
                DrawGameOver();
                break;
           case score:
                scoresLogic();
                break;
            
        }

        if (event.key.keysym.sym==SDLK_RIGHT)
        {
            doodler.pos.x+=20;
            doodler_temp=doodler_right;
        }
        if (event.key.keysym.sym==SDLK_LEFT)
        {
            doodler.pos.x-=20;
            doodler_temp=doodler_left;
        }
		
 

		SDL_UpdateScreen();
		SDL_Delay(1000/60);
	}
	return 0;
}




void LoadImages()
{

    doodler_right=ImgLoader(PATH"resource/image/doodleRight.png");
    
    doodler_left=ImgLoader(PATH"resource/image/doodleLeft.png");
    
    doodler_up=ImgLoader(PATH"resource/image/doodleUp.png");
    
    doodler_nose=ImgLoader(PATH"resource/image/doodleNose.png");
    
    //blocks
    green_block=ImgLoader(PATH"resource/image/blgreen.png");
    
    blue_block=ImgLoader(PATH"resource/image/blblue.png");

    fake_blockf0=ImgLoader(PATH"resource/image/fakef1.png");
    fake_blockf1=fake_blockf0;
    fake_blockf2=ImgLoader(PATH"resource/image/fakef2.png");
    fake_blockf3=ImgLoader(PATH"resource/image/fakef3.png");
    fake_blockf4=ImgLoader(PATH"resource/image/fakef4.png");

    Gray_block=ImgLoader(PATH"resource/image/blgray.png");
    
    white_block=ImgLoader(PATH"resource/image/white.png");

    YtoR_block=ImgLoader(PATH"resource/image/doodleRight.png");
  
    //enemy
    monster1f1=ImgLoader(PATH"resource/image/monsteronef1.png");
    monster1f2=ImgLoader(PATH"resource/image/monsteronef2.png");
    monster1f3=ImgLoader(PATH"resource/image/monsteronef3.png");
    monster1f4=ImgLoader(PATH"resource/image/monsteronef4.png");

    monster2f1=ImgLoader(PATH"resource/image/monstertwof1.png");
    monster2f2=ImgLoader(PATH"resource/image/monstertwof2.png");

    monster3=ImgLoader(PATH"resource/image/monsterthree.png");
    
    monster4=ImgLoader(PATH"resource/image/monsterfour.png");

    monster5f1=ImgLoader(PATH"resource/image/monsterfivef1.png");
    monster5f2=ImgLoader(PATH"resource/image/monsterfivef1.png");
    monster5f3=ImgLoader(PATH"resource/image/monsterfivef1.png");
    monster5f4=ImgLoader(PATH"resource/image/monsterfivef1.png");
    monster5f5=ImgLoader(PATH"resource/image/monsterfivef1.png");

    monster6=ImgLoader(PATH"resource/image/monstersix.png");
    
    black_hole=ImgLoader(PATH"resource/image/hole.png");

    UFOf1=ImgLoader(PATH"resource/image/ufof1.png");
    UFOf2=ImgLoader(PATH"resource/image/ufof2.png");

    //springers
    springf1=ImgLoader(PATH"resource/image/springf1.png");
    springf2=ImgLoader(PATH"resource/image/springf2.png");

    spring_shoesf1=ImgLoader(PATH"resource/image/Springshoesf1.png");
    spring_shoesf2=ImgLoader(PATH"resource/image/Springshoesf1.png");
    spring_shoesf3=ImgLoader(PATH"resource/image/Springshoesf1.png");
    spring_shoesf4=ImgLoader(PATH"resource/image/Springshoesf1.png");
    spring_shoesf5=ImgLoader(PATH"resource/image/Springshoesf1.png");

    trampolinef1=ImgLoader(PATH"resource/image/trampolinf1.png");
    trampolinef2=ImgLoader(PATH"resource/image/trampolinf2.png");
    trampolinef3=ImgLoader(PATH"resource/image/trampolinf3.png");

    //flyer
    jetpackf1=ImgLoader(PATH"resource/image/jetpackf11.png");
    jetpackf2=ImgLoader(PATH"resource/image/jetpackf2.png");
    jetpackf3=ImgLoader(PATH"resource/image/jetpackf3.png");
    jetpackf4=ImgLoader(PATH"resource/image/jetpackf4.png");
    jetpackf5=ImgLoader(PATH"resource/image/jetpackf5.png");
    jetpackf6=ImgLoader(PATH"resource/image/jetpackf6.png");
    jetpackf7=ImgLoader(PATH"resource/image/jetpackf7.png");
    jetpackf8=ImgLoader(PATH"resource/image/jetpackf8.png");
    jetpackf9=ImgLoader(PATH"resource/image/jetpackf9.png");
    jetpackf10=ImgLoader(PATH"resource/image/jetpackf10.png");

    capf1=ImgLoader(PATH"resource/image/capf1.png");
    capf2=ImgLoader(PATH"resource/image/capf2.png");
    capf3=ImgLoader(PATH"resource/image/capf3.png");
    capf4=ImgLoader(PATH"resource/image/capf4.png");
    //shield
    shield=ImgLoader(PATH"resource/image/Shield.png");
    shieldf1=ImgLoader(PATH"resource/image/shieldf1.png");
    shieldf2=ImgLoader(PATH"resource/image/shieldf2.png");
    shieldf3=ImgLoader(PATH"resource/image/shieldf3.png");
    //butts
    play=ImgLoader(PATH"resource/image/play.png");
    playon=ImgLoader(PATH"resource/image/playon.png");
    loading=ImgLoader(PATH"resource/image/loading.png");
    menu=ImgLoader(PATH"resource/image/menu.png");
    menuon=ImgLoader(PATH"resource/image/menuon.png");
    option=ImgLoader(PATH"resource/image/options.png");
    optionon=ImgLoader(PATH"resource/image/optionson.png");
    playagain=ImgLoader(PATH"resource/image/playagain.png");
    playagainon=ImgLoader(PATH"resource/image/playagainon.png");
    resume=ImgLoader(PATH"resource/image/resume.png");
    scores=ImgLoader(PATH"resource/image/scores.png");
    scoreson=ImgLoader(PATH"resource/image/scoreson.png");

    bar=ImgLoader(PATH"resource/image/bar.png");
    insect1=ImgLoader(PATH"resource/image/insect1.png");
    insect2=ImgLoader(PATH"resource/image/insect2.png");
    insect3=ImgLoader(PATH"resource/image/insect3.png");

    doodle_jump=ImgLoader(PATH"resource/image/doodle.png");
    //background    
    back_ground=ImgLoader(PATH"resource/image/background.png");

	nose= ImgLoader("assets/images/liknjuska_X.png",255,255,255); 
	lik =ImgLoader("assets/images/likpucaodskok_X.png",255,255,255);
}
void LoadFonts()
{
	Doodlejump80=TTF_OpenFont(PATH"resource/fonts/DoodleJump.ttf",80);
	Doodlejump70=TTF_OpenFont(PATH"resource/fonts/DoodleJump.ttf",70);
	Doodlejump60=TTF_OpenFont(PATH"resource/fonts/DoodleJump.ttf",60);
	Doodlejump50=TTF_OpenFont(PATH"resource/fonts/DoodleJump.ttf",50);
	Doodlejump30=TTF_OpenFont(PATH"resource/fonts/DoodleJump.ttf",30);
	Doodlejump20=TTF_OpenFont(PATH"resources/fonts/DoodleJump.ttf",20);
}

void LoadAudioes()
{
	jump=LoadSound(PATH"resources/audio/jump.ogg");
	feder=LoadSound(PATH"resources/audio/feder.ogg");
	jetpack=LoadSound(PATH"resources/audio/jetpack5.ogg");
	fakeblock=LoadSound(PATH"resources/audio/fakeBlock.ogg");
	monsterblizu=LoadSound(PATH"resources/audio/monsterblizu.ogg");
	propeller5=LoadSound(PATH"resources/audio/propeller5.ogg");
	springshoes=LoadSound(PATH"resources/audio/springshoes.ogg");
	trampoline=LoadSound(PATH"resources/audio/trampoline.ogg");
	ufo=LoadSound(PATH"resources/audio/ufo.ogg");
	basic_throw=LoadSound(PATH"resources/audio/basic_throw.ogg");
	fall=LoadSound(PATH"resources/audio/fall.ogg");

	
}
void CreateOptionsSurfaces()
{
	op_sounds=TTF_RenderText_Solid(Doodlejump80,"sounds",0,0,0);
	op_sounds_off_gray=TTF_RenderText_Solid(Doodlejump50,"OFF",140,140,140);
	op_sounds_off_green=TTF_RenderText_Solid(Doodlejump50,"OFF",0,100,0);
	op_sounds_on_gray=TTF_RenderText_Solid(Doodlejump50,"ON",140,140,140);
	op_sounds_on_green=TTF_RenderText_Solid(Doodlejump50,"ON",0,100,0);


}
void LoadResources()
{
    LoadImages();
    LoadAudioes();
    LoadFonts();
}

void mainmenuevariables()
{
    bl_green_menu.pos.x=60;
    bl_green_menu.pos.y=screen_height-250;
    doodlermain.height=124;
    doodlermain.pos.y=bl_green_menu.pos.y-doodlermain.height;
    jump_time=0.3;
    jump_length = doodlermain.pos.y-(screen_height/2-100);
    a=(jump_length*2)/jump_time;;
    x=0;
    t=0;
    x0=doodlermain.pos.y;v=-pow(2*a*jump_length,0.5);
}


inline bool IsMouseOnPlayItem()
{
	return (Mouse.x > 100 && Mouse.x < 324 &&
			Mouse.y > 256 && Mouse.y < 256+88);
}
inline bool IsMouseOnOptions()
{
	return (Mouse.x > screen_width-140 && Mouse.x < screen_width-140+114 &&
			Mouse.y > screen_height-120 && screen_height-120+95);
}
inline bool IsMouseOnScores()
{
	return (Mouse.x > screen_width-256 && Mouse.x < screen_width-256+100 &&
			Mouse.y > screen_height-125 && Mouse.y < screen_height-125+100);
}
inline bool IsMouseOnOn()
{
	return (Mouse.x > screen_width/2+20 && Mouse.x < screen_width/2+80 &&
			Mouse.y > screen_height/2-100 && Mouse.y < screen_height/2-100+50);
}
inline bool IsMouseOnOff()
{
	return (Mouse.x > screen_width/2-60 && Mouse.x < screen_width/2+10 &&
			Mouse.y > screen_height/2-100 && Mouse.y < screen_height/2-100+50);
}
inline bool IsMouseOnmenu()
{
	return (Mouse.x > 10 && Mouse.x < 234 &&
			Mouse.y > screen_height-98 && Mouse.y < screen_height-10);
}
inline bool IsMouseOnScoremenu()
{
	return (Mouse.x > 220 && Mouse.x < 444 &&
			Mouse.y > screen_height-98 && Mouse.y < screen_height-10);
}
inline bool IsMouseOnPlayAgainmenu()
{
	return (Mouse.x > 220 && Mouse.x < 444 &&
			Mouse.y > screen_height-208 && Mouse.y < screen_height-120);
}
inline void menudoodleLogic()
{
    //doodler
    x=0.5*a*pow(t,2)+v*t+x0;
    t+=0.04;
    doodlermain.pos.y=x;
    if (doodlermain.pos.y>bl_green_menu.pos.y-doodlermain.height)
    {
        x=0;t=0;
        if (sound_flag)
            PlaySound(jump);
    }
}

inline void menulogic()
{

    //mouse
    //	Check 'Play' item
	if(IsMouseOnPlayItem())
		if(Mouse.left)
		{
            point=0;
			currScreen=playGround;
            doodlerVariables();
            gameplay++;
			Mouse.left=false;
		}
		else
			playItem.MouseStatus=OnIt;
	else
		playItem.MouseStatus=Nothing;

	//	Check 'options' item
	if(IsMouseOnOptions())
        if(Mouse.left)
        {
            currScreen=options;
            Mouse.left=false;
        }
        else
		optionsItem.MouseStatus=OnIt;
	else
		optionsItem.MouseStatus=Nothing;

    //	Check 'scores' item
	if(IsMouseOnScores())
        if(Mouse.left)
        {
            currScreen=score;
            Mouse.left=false;
        }
        else
		scoresItem.MouseStatus=OnIt;
	else
		scoresItem.MouseStatus=Nothing;
    //	Check 'on' item
	if(IsMouseOnOn())
		if(Mouse.left)
		{
			sound_flag=true;
		//	InitLevel();
			Mouse.left=false;
		}
		else
			onItem.MouseStatus=OnIt;
	else
		onItem.MouseStatus=Nothing;

    if(IsMouseOnOff())
		if(Mouse.left)
		{
			sound_flag=false;
		//	InitLevel();
			Mouse.left=false;
		}
		else
			offItem.MouseStatus=OnIt;
	else
		offItem.MouseStatus=Nothing;

        //	Check 'menu' item
	if(IsMouseOnmenu())
		if(Mouse.left)
		{
            currScreen=MainMenue;
			//InitLevel();
			Mouse.left=false;
		}
		else
			menuItem.MouseStatus=OnIt;
	else
		menuItem.MouseStatus=Nothing;

    if(IsMouseOnScoremenu())
		if(Mouse.left)
		{
            currScreen=MainMenue;
			//InitLevel();
			Mouse.left=false;
		}
		else
			scoremenuItem.MouseStatus=OnIt;
	else
		scoremenuItem.MouseStatus=Nothing;

    if(IsMouseOnPlayAgainmenu())
		if(Mouse.left)
		{
            point=0;
            currScreen=playGround;
            doodlerVariables();
			gameplay++;
            Mouse.left=false;
		}
		else
			PAmenuItem.MouseStatus=OnIt;
	else
		PAmenuItem.MouseStatus=Nothing;

}

inline void DrawMainMenue ()
{
    menulogic();
    menudoodleLogic();
    CreateOptionsSurfaces();

    //	Draw the play item
	switch(playItem.MouseStatus)
	{
	case Nothing:
		SDL_BlitSurface(play,screen,100,256);
		break;
	case OnIt:
		SDL_BlitSurface(playon,screen,100,256);
		break;
	}

    //	Draw the options item
	switch(optionsItem.MouseStatus)
	{
	case Nothing:
        SDL_BlitSurface(option,screen,screen_width-140,screen_height-120);
		break;
	case OnIt:
       SDL_BlitSurface(optionon,screen,screen_width-140,screen_height-120);
		break;
	}

    //	Draw the scores item
	switch(scoresItem.MouseStatus)
	{
	case Nothing:
        SDL_BlitSurface(scores,screen,screen_width-256,screen_height-125);
		break;
	case OnIt:
        SDL_BlitSurface(scoreson,screen,screen_width-256,screen_height-125);
		break;
	}
    SDL_BlitSurface(green_block,screen,bl_green_menu.pos.x,bl_green_menu.pos.y);
    SDL_BlitSurface(black_hole,screen,screen_width-240,screen_height/2-100);
    SDL_BlitSurface(fake_blockf1,screen,screen_width-225,screen_height/2+50);
    SDL_BlitSurface(doodle_jump,screen,30,80);
    SDL_BlitSurface(doodler_right,screen,65,doodlermain.pos.y);

}

inline void DrawOptionsMenue ()
{
    menulogic();
    SDL_BlitSurface(op_sounds,screen,(screen_width)/2-90,screen_height/2-200);

    //	Draw the play item
	switch(sound_flag)
	{
	case true:
        SDL_BlitSurface(op_sounds_off_gray,screen,(screen_width)/2-60,screen_height/2-100);
        SDL_BlitSurface(op_sounds_on_green,screen,(screen_width)/2+20,screen_height/2-100);
		break;
	case false:
        SDL_BlitSurface(op_sounds_off_green,screen,(screen_width)/2-60,screen_height/2-100);
        SDL_BlitSurface(op_sounds_on_gray,screen,(screen_width)/2+20,screen_height/2-100);
		break;
	}
 

    //	Draw the menu item
	switch(menuItem.MouseStatus)
	{
	case Nothing:
        SDL_BlitSurface(menu,screen,10,screen_height-98);
		break;
	case OnIt:
       SDL_BlitSurface(menuon,screen,10,screen_height-98);
		break;
	}
    

}

void blucksLogic ()
{
    
    
    srand (time(NULL));
    if(basegamescreen)
    {
        bluck[0].pos.x=rand()%100+200;
        bluck [0].pos.y  = xplace;
        bluck [0].life   = 1;
        bluck [0].Type = GreenBlock;
        bluck [0].width  = 114;
        bluck [0].height = 30;
        xplace-=40;

        for (int i=1; i<40 ; i++)
        {
            bluck [i].pos.x  = rand()%520;
            bluck [i].pos.y  = xplace;
            bluck [i].life   = rand()%2;
            cheker++;
            if (bluck[i].life==true)
                cheker=0;
        //chanses
            type = rand()%8;
            if (type>=1 or type<=7)
            {
                bluck [i].Type = GreenBlock;
                bluck [i].width  = 114;
                bluck [i].height = 30;
            }
            if(type==0)
            {
                bluck [i].Type = FakeBlock;
                bluck [i].width  = 120;
                bluck [i].height = 30;
            }
        //cheker
            if (cheker>=5)
            {
                bluck[i].life   = true;
                bluck [i].Type = GreenBlock;
                bluck [i].width  = 114;
                bluck [i].height = 30;
            }
            xplace-=40;
        }

    }
    basegamescreen=false;

    
    tempo.pos.y = bluck[39].pos.y;
    for(int i=0; i<40; i++)
    {
        if(bluck[i].pos.y>screen_height)
        {
            cheker=0;

            for(int k=0; k<i; k++)
            {
                bluck.erase(bluck.begin()+k);
                bluck_temp.pos.x  = rand()%520;
                bluck_temp.pos.y  = xplace;
                temp=rand()%3;
                if (temp==0 or temp==1)
                    bluck_temp.life   = 0;
                if (temp==2)
                    bluck_temp.life   = 1;
                cheker++;
            
            //chanses
                type = rand()%21;
                if (type>=4 && type<=20)
                {
                    bluck_temp.Type = GreenBlock;
                    bluck_temp.width  = 114;
                    bluck_temp.height = 30;
                }
                if (type==3)
                {
                    bluck_temp.Type = whiteBlock;
                    bluck_temp.width  = 114;
                    bluck_temp.height = 30;
                }
                if(type>=1 && type<=2)
                {
                    bluck_temp.Type = FakeBlock;
                    bluck_temp.width  = 120;
                    bluck_temp.height = 30;
                }
                if(type==0)
                {
                    bluck_temp.Type = BlueBlock;
                    bluck_temp.moveFlag=rand()%2;
                    bluck_temp.width  = 120;
                    bluck_temp.height = 30;
                }
            //cheker
                if (bluck_temp.life==true && bluck_temp.Type!=FakeBlock)
                    cheker=0;
                if (cheker>=3)
                {
                    bluck_temp.life   = true;
                    bluck_temp.Type = GreenBlock;
                    bluck_temp.width  = 114;
                    bluck_temp.height = 30;
                }
                xplace-=40;
                bluck.push_back(bluck_temp);
                
            }
                // short int object=rand()%100;
                // if (object==0)
                // {
                //     shieldObject.life=true;
                //     shieldObject.pos.x= screen_width/2;//bluck_temp.pos.x+10;
                //     shieldObject.pos.y= screen_height/2;//bluck_temp.pos.y-100;
                //     shieldLogic();
                // }
        }
        
        if (bluck[i].Type == BlueBlock)
        {
            if(bluck[i].moveFlag)
                bluck[i].pos.x+=4;
            else
                bluck[i].pos.x-=4;
            if (bluck[i].pos.x>=screen_width-120)
                bluck[i].moveFlag=false;
            if (bluck[i].pos.x<=0)
                bluck[i].moveFlag=true;
        }    
        
        
    }
    
    for (int i=0; i<40; i++)
    {
        if (bluck[i].life==true and bluck[i].Type==GreenBlock)
         SDL_BlitSurface(green_block,screen,bluck[i].pos.x,bluck[i].pos.y);
        if (bluck[i].life==true and bluck[i].Type==FakeBlock)
         SDL_BlitSurface(fake_blockf1,screen,bluck[i].pos.x,bluck[i].pos.y);
         if (bluck[i].life==true and bluck[i].Type==FakeBlock0)
         SDL_BlitSurface(fake_blockf4,screen,bluck[i].pos.x,bluck[i].pos.y);
        if (bluck[i].life==true and bluck[i].Type==BlueBlock)
         SDL_BlitSurface(blue_block,screen,bluck[i].pos.x,bluck[i].pos.y);
        if (bluck[i].life==true and bluck[i].Type==whiteBlock)
         SDL_BlitSurface(white_block,screen,bluck[i].pos.x,bluck[i].pos.y);


    }

}
void doodlerVariables()
{
    
    doodler.width           = 124;//96-38;
    doodler.height          = 120;
    doodler.pos.x           = screen_width/2-124/2;
    doodler.pos.y           = screen_height;
    doodler_jump_time       = 1.25;
    doodler_jump_length     = screen_height-80-screen_height/2;
    doodler_a               = (doodler_jump_length*2)/doodler_jump_time;
    doodler_x0              = doodler.pos.y;
    doodler_v0              = -pow(2*doodler_a*doodler_jump_length,0.5);
    doodler_t               = 0;
    doodler_vbar            = doodler_jump_length/doodler_jump_time;
}
void doodlerLogic()
{
    SDL_BlitSurface(doodler_temp,screen,doodler.pos.x,doodler.pos.y);

    doodler.pos.y   = 0.5 * doodler_a * pow(doodler_t,2) + doodler_v0 * doodler_t + doodler_x0;
    doodler_v       = doodler_a * doodler_t + doodler_v0;
    doodler_t      += 0.04;
    
    if (doodler_v>=0)
    {
        for(int i=0; i<40; i++)
        {
            if (bluck[i].life==true     &&    
                doodler.pos.y+doodler.height>=bluck[i].pos.y-10 && 
                doodler.pos.y+doodler.height<bluck[i].pos.y+35 &&
                doodler.pos.x+35>bluck[i].pos.x-45 &&
                doodler.pos.x+35<bluck[i].pos.x+114 &&
                bluck[i].Type!=FakeBlock && bluck[i].Type!=FakeBlock0)
                {
                    scrolDown = screen_height-100-bluck[i].pos.y;
                    point+=scrolDown;
                    if (scrolDown>=0)
                    {
                        doodler.pos.y+=scrolDown;
                        for (int i=0; i<40 ; i++)
                        {
                            bluck[i].pos.y+=scrolDown;
                        }
                        xplace+=scrolDown;
                        if (bluck[i].Type==whiteBlock)
                        {
                            bluck[i].life=false;

                        }
                     

                    }
                    doodler_t=0;
                    doodler_x0 = doodler.pos.y;
                  //  doodler.pos.y=bluck[i].pos.y-doodler.height;
                    if (sound_flag)
                       PlaySound(jump);

                }
            if (bluck[i].life==true     &&    
                doodler.pos.y+doodler.height>=bluck[i].pos.y-10 && 
                doodler.pos.y+doodler.height<bluck[i].pos.y+35 &&
                doodler.pos.x+35>bluck[i].pos.x-45 &&
                doodler.pos.x+35<bluck[i].pos.x+114 &&
                bluck[i].Type==FakeBlock )
                {
                    bluck[i].Type=FakeBlock0;
                    PlaySound(fakeblock);
                }

        }

    }

        scrolDown=0;
    

    if(doodler.pos.y>screen_height)
    {
        currScreen=GameOver;
        PlaySound(fall);
        doodler.pos.y-=screen_height+200;
        doodler_t=0;
        doodler_x0 = doodler.pos.y;
        


    }
    if(doodler.pos.x>screen_width)
        doodler.pos.x=0;
    if(doodler.pos.x<-70)
        doodler.pos.x=screen_width;
}
void DrawDoodler ()
{
    sprintf(Point, "%d", point);    
    
    SDL_BlitSurface(bar,screen,0,0);
    SDL_BlitSurface(TTF_RenderText_Solid(Doodlejump50,Point,0,0,0),screen,10,5);


    doodlerLogic();
}
// void shieldLogic()
// {
    
    
//     if (doodler.pos.x+62>shieldObject.pos.x       &&
//         doodler.pos.x+62<shieldObject.pos.x+191   &&
//         doodler.pos.y+60>shieldObject.pos.y       &&
//         doodler.pos.y+60<shieldObject.pos.y+189)
//         {
//             monsters.life=false;
//             shield_time-=0.04;
//             shieldObject.pos.x=doodler.pos.x;
//             shieldObject.pos.y=doodler.pos.y;
//         }
//     if (shield_time<=0)
//         {
//             shieldObject.life=false;
//             monsters.life=true;
//             shield_time=10;
//         }
//     if (shieldObject.life=true)
//          SDL_BlitSurface(shieldf1,screen,shieldObject.pos.x,shieldObject.pos.y);


    
// }
void DrawGameOver ()
{
    menulogic();
    SDL_BlitSurface(TTF_RenderText_Solid(Doodlejump80,"Game Over! ",200,0,0),screen,80,300);
    SDL_BlitSurface(TTF_RenderText_Solid(Doodlejump60,"your score: ",0,0,0),screen,100,400);
    SDL_BlitSurface(TTF_RenderText_Solid(Doodlejump60,Point,0,0,0),screen,400,400);
    SDL_BlitSurface(doodler_temp,screen,doodler.pos.x,doodler.pos.y);


    doodler.pos.y   = 0.5 * doodler_a * pow(doodler_t,2) + doodler_v0 * doodler_t + doodler_x0;
    doodler_v       = doodler_a * doodler_t + doodler_v0;
    doodler_v*=-1;
    doodler_t      += 0.06;

    score_temp=point;
    playerScore[gameplay-1]=point;
    //point=0;
    //	Draw the menu item
	switch(scoremenuItem.MouseStatus)
	{
	case Nothing:
        SDL_BlitSurface(menu,screen,220,screen_height-98);
		break;
	case OnIt:
       SDL_BlitSurface(menuon,screen,220,screen_height-98);
		break;
	}
    switch(PAmenuItem.MouseStatus)
	{
	case Nothing:
        SDL_BlitSurface(playagain,screen,220,screen_height-208);
		break;
	case OnIt:
       SDL_BlitSurface(playagainon,screen,220,screen_height-208);
		break;
	}
}
void bubble_sort() 
{
    for (int i = 0; i < playerScore.size(); i++)
        for (int j = 0; j <playerScore.size()-i-1; j++)
            if (playerScore[j + 1] > playerScore[j])
                swap(playerScore[j], playerScore[j + 1]);
}
void scoresLogic()
{
    menulogic();
    SDL_BlitSurface(TTF_RenderText_Solid(Doodlejump80,"High Scores!",150,0,0),screen,20,20);

    //	Draw the menu item
	switch(menuItem.MouseStatus)
	{
	case Nothing:
        SDL_BlitSurface(menu,screen,10,screen_height-98);
		break;
	case OnIt:
       SDL_BlitSurface(menuon,screen,10,screen_height-98);
		break;
    }

    for(int i=1; i<=10 ; i++)
    {
        char tempch[2];
        sprintf(tempch, "%d", i);  
        bubble_sort();  
        SDL_BlitSurface(TTF_RenderText_Solid(Doodlejump80,tempch,0,0,0),screen,300,i*80);
        sprintf(tempch, "%d", playerScore[i-1]);  
        SDL_BlitSurface(TTF_RenderText_Solid(Doodlejump80,tempch,0,0,0),screen,400,i*80);


               
    }
            menudoodleLogic();
        SDL_BlitSurface(doodler_right,screen,55,doodlermain.pos.y);
        SDL_BlitSurface(green_block,screen,bl_green_menu.pos.x,bl_green_menu.pos.y);

}
// void noselogic()
// {
//     	float rad = atan2(cx -Mouse.x , cy -Mouse.y);
// 		float deg = 180 * rad / M_PI;
// 		rotated = rotozoomSurface(nose,deg,1,1);
// 		SDL_BlitSurface(lik,screen,cx-(lik->w)/2,cy-(lik->h)/2-10);
// 		SDL_BlitSurface(rotated,screen,cx-(rotated->w)/2,cy-(rotated->h)/2);
// }