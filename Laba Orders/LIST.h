#pragma once
#include"cord.h"
struct Node
{
	cord *info;
	Node* next;
	Node* prev;
};
typedef Node* Tlist;

class LIST
{
private:
	Tlist begin;
	Tlist end;
public:
	Tlist getbegin();
	Tlist getend();
	LIST(cord *x);
	void AddAft(Tlist Q, cord *x);
	void Delete(Tlist Q);
	void Print();
	~LIST();
};

