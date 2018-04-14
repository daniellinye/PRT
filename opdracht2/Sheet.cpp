#include "Cell.cpp"
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

class Sheet
{
private:
	std::vector<std::vector<Cell*>> matrix;
	//temporary empty cell
	int h, b;
public:
	Sheet(int h, int b)
	{
		this->h = h;
		this->b = b;
		//fill matrix with h x b cells that are empty
		matrix.resize(b, std::vector<Cell*>(h, new Cell));
	}
	
	template<typename T>
	CellValue<T>* getCell(int x, int y)
	{
		matrix[x][y]->giveref();
	}

	template<typename T>
	CellValue<T>* getCell(char a, int y)
	{
		if (a >= 'A' && a <= 'Z')
			return matrix[a - 'A'][y]->giveref();
		else
			return NULL;
	}

	//TODO: move to class Range
	Cell* begin(int column)
	{
		return matrix[column][0];
	}

	//TODO: move to class Range
	Cell* end(int column)
	{
		return matrix[column][h];
	}

	void print()
	{
		int tx = 0;
		for(std::vector<Cell*> list : matrix)
		{
			for(Cell* element : list)
			{
				cout << element->giveref()->convertfloat();
				tx++;
				if (tx == b)
				{
					cout << endl;
					tx = 0;
				}
			}
		}
	}
};