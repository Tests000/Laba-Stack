#pragma once
#include<SFML/Graphics.hpp>
#include"LIST.h"
#include<string>
#include<sstream>
using namespace sf;

LIST* Interface(RenderWindow &window, int** Matrix);
int result(RenderWindow& window, LIST* list, int** Matrix);