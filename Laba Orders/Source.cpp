#include"Interface.h"
#include<Windows.h>
RenderWindow window(VideoMode(1000, 1000), "Wild Horse");
bool TaskTest(int** Matrix, LIST *list);
void CreateMatr(int**& Matrix);
bool DeleteMatrix(int** Matrix);
int main()
{	
	int** Matrix;
	LIST* list;
	do {
		CreateMatr(Matrix);
		list = Interface(window, Matrix);
		TaskTest(Matrix, list);
	} while (result(window, list, Matrix) != 7&&DeleteMatrix(Matrix));
}

void Clear(int** Matrix)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (Matrix[i][j] == -2)
				Matrix[i][j] = 0;
}

bool TaskTest(int** Matrix, LIST* list)
{
	bool result = false, found;
	int x, y;
	int count = 1;
	while (!result)
	{
		cord* t = list->getend()->info;
		x = t->x;
		y = t->y;
		Matrix[y][x] = count;
		found = false;
		for (int i = 2, j = -1; abs(i) > 0&&!found&&!result; i *= -1, j *= -1)
		{
			for (int k = 0; k < 2&&!found && !result; j *= -1, k++)
				if (y + i >= 0 && y + i < 8 && x + j >= 0 && x + j < 8 && (Matrix[y + i][x + j] == 0 || Matrix[y + i][x + j] == -3))
				{
					y += i;
					x += j;
					cord* t = new cord(x, y);
					list->AddAft(list->getend(), t);
					count++;
					found = true;
				}
			if (j > 0)
				j++;
			if (i < 0)
				i++;
		}
		if(!found)
		{
			if (count == 1)
				result = true;
			else
			{
				Matrix[y][x] = -2;
				count--;
				list->Delete(list->getend());
			}
		}
		if (Matrix[y][x] == -3)
			result = true;
	}
	if (count == 1)
		result = false;
	Clear(Matrix);
	return result;
}

void CreateMatr(int**& Matrix)
{
	Matrix = new int* [8];
	for (int i = 0; i < 8; i++)
	{
		Matrix[i] = new int[8];
	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Matrix[i][j] = 0;
	Matrix[0][0] = 1;
	Matrix[7][7] = -3;
}

bool DeleteMatrix(int**Matrix)
{
	for (int i = 0; i < 8; i++)
		delete[] Matrix[i];
	delete[] Matrix;
	return true;
}

//int TaskRec(int** Matrix, LIST *list, int count)
//{
//	int count = 1;
//	int countmin = 65;
//	cord* t = new cord(list->getend()->info->x, list->getend()->info->y);
//	if(Matrix[t->y][t->x] == 0)
//	{
//		Matrix[t->y][t->x] = count;
//		for (int i = 2, j = -1; abs(i) > 0; i *= -1, j *= -1)
//		{
//			for (int k = 0; k < 2; j *= -1, k++)
//				if (t->y + i >= 0 && t->y + i < 8 && t->x + j >= 0 && t->x + j < 8 && Matrix[t->y + i][t->x + j] == 0)
//				{
//					t->y += i;
//					t->x += j;
//					list->AddAft(list->getend(), t);
//					countmin=TaskRec(Matrix, list, count);
//				}
//			if (j > 0)
//				j++;
//			if (i < 0)
//				i++;
//		}
//	}
//	else if (Matrix[t->y][t->x] == -3)
//	{
//		if (count < countmin)
//		{
//			count = countmin;
//		}
//		list->Delete(list->getend());
//	}
//	Clear(Matrix);
//	return countmin;
//}
//
//LIST* CopyList(LIST* list)
//{
//	LIST *listcopy
//}