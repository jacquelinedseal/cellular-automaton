
#include <iostream>
#include <vector>
#include <array>
#include <iomanip>

using namespace std;

void printGrid(const vector< vector<int> >& gridLayout);
void setUpGrid(vector < vector<int> >& gridLayout, int gridL, int gridW);
void addGridBorder0(vector < vector<int> >& gridLayout, int& gridL, int& gridW);
int countCell(vector<vector<int> > &gridLayout, int gridL, int gridW, int xPos, int yPos, const array <int, 8>& xInc, const array <int, 8>& yInc);
int calcNextState(int cellState, int countAlive);
bool checkBounds(int xPos, int yPos, int gridL, int gridW);

int main()
{
    int gridL, gridW, numGen, numCell, indexX, indexY, liveC;
    bool needZeroBuffer = false;
    array <int, 8> xIncrement{1, 0, -1, -1, -1, 0, 1, 1};
    array <int, 8> yIncrement{-1, -1, -1, 0, 1, 1, 1, 0};

    do
    {
        cout << "Please enter the length of the grid: ";
        cin >> gridL;
    }while(gridL <= 0);

    do
    {
        cout << "Please enter the width of the grid: ";
        cin >> gridW;
    }while(gridW <= 0);

    do
    {
        cout << "Please enter the number of generations: ";
        cin >> numGen;
    }while(numGen <= 0);

    vector< vector<int> > gridState(gridW);

    do
    {
        cout << "Please enter the number of live cells you wish to start with: ";
        cin >> numCell;
    }while(numCell <= 0 || numCell > gridL * gridW);

    setUpGrid(gridState, gridL, gridW);
    cout << '\n';

    for(int countC{0}; countC < numCell; countC++)
    {
        do
        {
            cout << "Please enter the x coordinate: ";
            cin >> indexX;
        }while(indexX < 0 || indexX >= gridL);

        do
        {
            cout << "Please enter the y coordinate: ";
            cin >> indexY;
        }while(indexY < 0 || indexY >= gridW);

        gridState[indexY][indexX] = 1;

        cout << '\n';
    }
    addGridBorder0(gridState, gridL, gridW);
    vector< vector<int> > prevGrid{gridState};

    printGrid(gridState);
    cout << "\n";

    cout << gridL << " " << gridW << endl;

    for(int countGen{0}; countGen < numGen; countGen++)
    {
        needZeroBuffer = false;
        for(size_t rowI{0}; rowI < gridW; rowI++)
        {
            for(size_t columnI{0}; columnI < gridL; columnI++)
            {
                liveC = countCell(prevGrid, gridL, gridW, columnI, rowI, xIncrement, yIncrement);
                gridState[rowI][columnI] = calcNextState(prevGrid[rowI][columnI], liveC);


                for(size_t i{0}; i < 8; i++)
                {
                    if(checkBounds((columnI + xIncrement[i]), (rowI + yIncrement[i]), gridL, gridW) == false && gridState[rowI][columnI] == 1)
                        needZeroBuffer = true;
                }
            }
        }

        if(needZeroBuffer == true)
            addGridBorder0(gridState, gridL, gridW);
        prevGrid = gridState;
        printGrid(gridState);
        cout << "\n";
    }

    return 0;
}

void printGrid(const vector< vector<int> >& gridLayout)
{
    for(auto row : gridLayout)
    {
        for(auto elem : row)
        {
            if(elem == 0)
                cout << setw(2) << " ";
            else
                cout << setw(2) << elem;
        }

        cout << endl;
    }
}

void setUpGrid(vector < vector<int> >& gridLayout, int gridL, int gridW)
{
    for(int rowI{0}; rowI < gridW; rowI++)
    {
        for(int elemI{0}; elemI < gridL; elemI++)
            gridLayout.at(rowI).push_back(0);
    }
}

int countCell(vector< vector<int> >& gridLayout, int gridL, int gridW, int xPos, int yPos, const array <int, 8>& xInc, const array <int, 8>& yInc)
{
    int aliveC{0};

    for(size_t i{0}; i < 8; i++)
    {
        if(checkBounds((xPos + xInc[i]), (yPos + yInc[i]), gridL, gridW) == true)
        {
            if(gridLayout[yPos + yInc[i]][xPos + xInc[i]] == 1)
                aliveC++;
        }
    }

    return aliveC;
}

int calcNextState(int cellState, int countAlive)
{
    int nextState = cellState;

    if(countAlive < 2)
        nextState = 0;
    else if(cellState == 1 && (countAlive == 2 || countAlive == 3))
        nextState = 1;
    else if(cellState == 0 && (countAlive == 3))
        nextState = 1;
    else if(countAlive > 3)
        nextState = 0;

    return nextState;
}

bool checkBounds(int xPos, int yPos, int gridL, int gridW)
{
    bool inBound;

    if(xPos < 0 || xPos >= gridL)
        inBound = false;
    else if(yPos < 0 || yPos >= gridW)
        inBound = false;
    else
        inBound = true;

    return inBound;
}

void addGridBorder0(vector < vector<int> >& gridLayout, int& gridL, int& gridW)
{
    gridW += 2;
    gridL += 2;
    vector< vector<int> > newGrid(gridW);

    setUpGrid(newGrid, gridL, gridW);

    for(size_t newRowI{1}; newRowI < gridW - 1; newRowI++)
    {
        for(size_t newColumnI{1}; newColumnI < gridL - 1; newColumnI++)
        {
            newGrid[newRowI][newColumnI] = gridLayout[newRowI - 1][newColumnI - 1];
        }
    }

    gridLayout = newGrid;
}

