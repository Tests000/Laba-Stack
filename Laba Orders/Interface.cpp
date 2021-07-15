#include "Interface.h"
Event event;
bool pr = false;
int step = 0;
void setHorse(RenderWindow& window, int** Matrix, int x, int y, LIST* list)
{
	if (!pr)
	{
		if (event.type == Event::MouseButtonPressed)
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (Matrix[y][x] != 1)
				{
					Matrix[y][x] = 1;
					Matrix[list->getbegin()->info->y][list->getbegin()->info->x] = 0;
					list->getbegin()->info->y = y;
					list->getbegin()->info->x = x;
					pr = true;
				}
			}
		}
	}
	else if (event.type == Event::MouseButtonReleased)
		pr = false;
}

void setAim(RenderWindow& window, int** Matrix, int x, int y, LIST* list)
{
	if (!pr)
	{
		if (event.type == Event::MouseButtonPressed)
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (Matrix[y][x] != 1&& Matrix[y][x] != -3)
				{
					Matrix[y][x] = -3;
					if(Matrix[list->getend()->info->y][list->getend()->info->x] != 1)
						Matrix[list->getend()->info->y][list->getend()->info->x] = 0;
					list->getend()->info->y = y;
					list->getend()->info->x = x;
					pr = true;
				}
			}
		}
	}
	else if (event.type == Event::MouseButtonReleased)
		pr = false;
}

void setChess(RenderWindow& window, int** Matrix, int x, int y)
{
	if (event.type == Event::MouseButtonPressed)
	{
		if (event.key.code == Mouse::Left && Matrix[y][x] == 0)
		{
			Matrix[y][x] = -1;
		}
		else if (event.key.code == Mouse::Right && Matrix[y][x] == -1)
		{
			Matrix[y][x] = 0;
		}
	}
}

void FindMouse(RenderWindow& window, int** Matrix, LIST* list)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	int x = pos.x / 100-1;
	int y = pos.y / 100-1;
	Texture image;
	image.loadFromFile("glass.png");
	Sprite sprite;
	sprite.setTexture(image);
	Font font;
	font.loadFromFile("20016.ttf");
	Text text("", font, 50);
	text.setFillColor(Color::Color(0, 0, 0));
	if (x >= 0 && x < 8 && y >= 0 && y < 8)
	{
		if (Matrix[y][x] == 0)
		{
			sprite.setPosition((x + 1) * 100, (y + 1) * 100);
			window.draw(sprite);
		}
		if (step == 0)
			setHorse(window, Matrix, x, y, list);
		else if (step == 1)
			setAim(window, Matrix, x, y, list);
		else if (step == 2)
			setChess(window, Matrix, x, y);
	}
	if (step == 0)
		text.setString("Select starting position");
	else if (step == 1)
		text.setString("Select the last position");
	else if (step == 2)
		text.setString("Place obstacles");
	text.setPosition(30, 30);
	window.draw(text);
	Texture imageH;
	imageH.loadFromFile("chessH.png");
	Sprite spriteH;
	spriteH.setTexture(imageH);
	spriteH.setPosition((list->getbegin()->info->x + 1) * 100 + 10, (list->getbegin()->info->y + 1) * 100 + 10);
	window.draw(spriteH);
}

void PrintBoard(RenderWindow& window, int** Matrix, LIST* list)
{
	RectangleShape square(Vector2f(100.f, 100.f));
	Font font;
	font.loadFromFile("20016.ttf");
	Text text("Hello", font, 50);
	text.setFillColor(Color::Color(101, 67, 33));
	Texture image;
	image.loadFromFile("chess.png");
	Sprite sprite;
	sprite.setTexture(image);
	Texture imageH;
	imageH.loadFromFile("geo.png");
	Sprite spriteH;
	spriteH.setTexture(imageH);
	char c;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 0)
				square.setFillColor(Color::Color(101, 67, 33));
			else
				square.setFillColor(Color::Color(245, 245, 220));
			square.setPosition((j + 1) * 100, (i + 1) * 100);
			window.draw(square);
			if (Matrix[i][j] == -1)
			{
				sprite.setPosition((j+1) * 100 + 36, (i+1) * 100 + 25);
				window.draw(sprite);
			}
			if (Matrix[i][j] == -3)
			{
				spriteH.setPosition((j + 1) * 100 + 25, (i + 1) * 100 + 25);
				window.draw(spriteH);
			}
		}
		c = i + 65;
		text.setString(c);
		text.setPosition(35 + 100*(i+1), 905);
		window.draw(text);
		c = 7 - i + 49;
		text.setString(c);
		text.setPosition(60, 100 * (i + 1)+ 25);
		window.draw(text);

	}
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	if (pos.x > 890 && pos.x < 970 && pos.y>890 && pos.y < 955)
	{
		text.setFillColor(Color::Color(0, 0, 255));
		if (!pr)
		{
			if (event.type == Event::MouseButtonPressed)
			{
				if (Mouse::isButtonPressed(Mouse::Left) && (step != 1 || step == 1 && Matrix[list->getend()->info->y][list->getend()->info->x] == -3))
				{
					text.setFillColor(Color::Color(255, 0, 0));
					step++;
				}
				pr = true;
			}
			
		}
		else if (event.type == Event::MouseButtonReleased)
			pr = false;
	}
	text.setString("next");
	text.setPosition(900, 900);
	window.draw(text);
}

LIST* Interface(RenderWindow& window, int** Matrix)
{
	step = 0;
	cord* beg = new cord(0, 0);
	LIST* list = new LIST(beg);
	cord* end = new cord(7, 7);
	list->AddAft(list->getbegin(), end);
	while (window.isOpen()&&step<3)
	{
		window.clear(Color(255, 255, 255));
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		PrintBoard(window, Matrix, list);
		FindMouse(window, Matrix, list);
		window.display();
	}
	list->Delete(list->getend());
	return list;
}

void PrintStep(RenderWindow& window, Tlist Q, int** Matrix)
{
	Font font;
	int count;
	std::string str;
	font.loadFromFile("20016.ttf");
	Text text("Hello", font, 50);
	text.setFillColor(Color::Color(0, 0, 0));
	while (Q->prev)
	{
		count=Matrix[Q->prev->info->y][Q->prev->info->x];
		std::stringstream ss;
		ss << count;
		str = ss.str();
		text.setString(str);
		text.setPosition((Q->prev->info->x+1)*100+27, (Q->prev->info->y + 1) * 100 + 20);
		window.draw(text);
		Q = Q->prev;
	}
}

void CheckButton(RenderWindow& window, Text text, int xbeg, int xend, int ybeg, int yend)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	if (pos.x > xbeg && pos.x < xend && pos.y>ybeg && pos.y <yend)
	{
		text.setFillColor(Color::Color(255, 0, 0));
		if (!pr)
		{
			if (event.type == Event::MouseButtonPressed)
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					if (xbeg == 250)
						step = 6;
					else
						step = 7;
				}
				pr = true;
			}

		}
		else if (event.type == Event::MouseButtonReleased)
			pr = false;
	}
	window.draw(text);
}

int result(RenderWindow& window, LIST* list, int** Matrix)
{
	Clock clock;
	int x, y;
	step = 3;
	bool flag=false, move = false;
	if (list->getend() != list->getbegin())
		flag = true;
	else
		step = 4;
	Texture imageH;
	imageH.loadFromFile("chessH.png");
	Sprite spriteH;
	spriteH.setTexture(imageH);
	Tlist Q = list->getbegin();
	cord Horse((Q->info->x+1) * 100 + 10, (Q->info->y+1) * 100 + 10);
	clock.restart();
	while (window.isOpen()&&step<6)
	{
		float time = clock.getElapsedTime().asMicroseconds();
		time /= 500;
		window.clear(Color(255, 255, 255));
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (flag&&step==3)
		{
			x = Q->next->info->x - Q->info->x;
			y = Q->next->info->y - Q->info->y;
			PrintBoard(window, Matrix, list);
			PrintStep(window, Q->next, Matrix);
			if (move&&abs((Q->next->info->x + 1) * 100 + 10 - Horse.x) < 10 && abs((Q->next->info->y + 1) * 100 + 10 - Horse.y) < 10)
			{
				spriteH.setPosition(Horse.x + x, Horse.y + y);
			}
			else
			{
				spriteH.setPosition((Q->next->info->x + 1) * 100 + 10, (Q->next->info->y + 1) * 100 + 10);
				if (time < 1000)
				{
					time = clock.getElapsedTime().asMicroseconds();
					time /= 500;
					move = false;
				}
				else
				{
					clock.restart();
					move = true;
					if (Q->next->next)
						Q = Q->next;
					else
						step = 4;
				}
				Horse.fill((Q->info->x + 1) * 100 + 10, (Q->info->y + 1) * 100 + 10);
			}
			window.draw(spriteH);
		}
		else if(!flag&&step==4)
		{
			Font font;
			font.loadFromFile("20016.ttf");
			Text text("", font, 150);
			text.setFillColor(Color::Color(0, 0, 0));
			text.setString("Way not found");
			PrintBoard(window, Matrix, list);
			text.setPosition(110, 400);
			spriteH.setPosition((list->getbegin()->info->x + 1) * 100 + 10, (list->getbegin()->info->y + 1) * 100 + 10);
			window.draw(text);
			window.draw(spriteH);
		}
		else if (step == 4)
		{
			PrintBoard(window, Matrix, list);
			PrintStep(window, list->getend(), Matrix);
			spriteH.setPosition((list->getend()->info->x + 1) * 100 + 10, (list->getend()->info->y + 1) * 100 + 10);
			window.draw(spriteH);
		}
		else if (step == 5)
		{
			Texture back;
			back.loadFromFile("background.png");
			Sprite backgr;
			backgr.setTexture(back);
			PrintBoard(window, Matrix, list);
			PrintStep(window, list->getend(), Matrix);
			Font font;
			font.loadFromFile("20016.ttf");
			Text text("", font, 50);
			text.setFillColor(Color::Color(40, 40, 40));
			backgr.setPosition(0, 0);
			window.draw(spriteH);
			window.draw(backgr);
			text.setString("Do you want to end program?");
			text.setPosition(200, 400);
			window.draw(text);
			text.setString("No");
			text.setPosition(250, 500);
			CheckButton(window, text, 250, 300, 500, 550);
			text.setString("Yes");
			text.setPosition(600, 500);
			CheckButton(window, text, 600, 650, 500, 550);
		}
		window.display();
	}
	return step;
}