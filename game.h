#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

 LARGE_INTEGER freq;

char gameMatrix[12][31];

char spaceship[6] = "<-i->";

int min_ship_dis = 1, max_ship_dis = 25;

int current_ship_coordinate=20;

int hp=3; //Health
int score=0;//Score

int astroid[5];
int astroidPosition=1;
int prevastroidPosition=1;

double PrevAttacktime;
double attacktime;
