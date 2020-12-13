#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <fstream> 


using namespace std;

bool liveOrDie(int mtrxelem, int aliveneibs) {
    if (mtrxelem == 1 && aliveneibs < 2) {
        return false;
    }
    else if (mtrxelem == 1 && (aliveneibs == 2 || aliveneibs == 3))
    {
        return true;
    }
    else if (mtrxelem == 1 && aliveneibs > 3)
    {
        return false;
    }
    else if (mtrxelem == 0 && aliveneibs == 3)
    {
        return true;
    }
    else if (mtrxelem == 0 && aliveneibs != 3)
    {
        return false;
    }
    else {
        return false;
    }
}


int replace_mtrx(int **&mtrx, int mtrxelem, int i, int j, int maxi, int maxj) {
    // mtrxelem - рассматриваемый элемент матрицы
    // maxi - строки
    // maxj - столбцы
    // выделяем расположение ячейки для поиска соответствующих ему соседей

    if (i == 0 && j == 0) // нулевой угловой элемент
    {
        if (liveOrDie(mtrxelem, (mtrx[0][1] + mtrx[1][0] + mtrx[1][1] + mtrx[0][maxj] + 
            mtrx[maxi][0] + mtrx[maxi][maxj] + mtrx[1][maxj] + mtrx[maxi][1]))){
            mtrxelem = 1;
        }
        else {
            mtrxelem = 0;
        }
    }

    else if (i == maxi && j == 0) // левый нижний угловой элемент
    {

        if (liveOrDie(mtrxelem, (mtrx[maxi - 1][0] + mtrx[maxi - 1][1] + mtrx[maxi][1] + mtrx[0][0] + mtrx[0][maxj] + 
            mtrx[maxi][maxj] + mtrx[maxi - 1][maxj] + mtrx[0][1])))
        {
            mtrxelem = 1;
        }
        else {
            mtrxelem = 0;
        }
        

    }

    else if (i == 0 && j == maxj) // правый верхний угловой элемент
    {

        if (liveOrDie(mtrxelem, (mtrx[0][maxj - 1] + mtrx[1][maxj - 1] + mtrx[1][maxj] + mtrx[maxi][maxj] + mtrx[0][0] + 
            mtrx[maxi][0] + mtrx[maxi][maxj - 1] + mtrx[1][0])))
        {
            mtrxelem = 1;
        }
        else {
            mtrxelem = 0;
        }
        
    }

    else if (i == maxi && j == maxj) // правый нижний угловой элемент
    {
        if (liveOrDie(mtrxelem, (mtrx[maxi][0] + mtrx[0][maxj] + mtrx[0][0] + mtrx[maxi][maxj - 1] + mtrx[maxi - 1][maxj] + 
            mtrx[maxi - 1][maxj - 1] + mtrx[maxi - 1][0] + mtrx[0][maxj - 1])))
        {
            mtrxelem = 1;
        }
        else {
            mtrxelem = 0;
        }
    }

    else if (i == 0 && j != 0 && j != maxj) // верхняя грань матрицы
    {
         if (liveOrDie(mtrxelem, (mtrx[i + 1][j] + mtrx[i + 1][j - 1] + mtrx[i + 1][j + 1] + 
             mtrx[i][j + 1] + mtrx[i][j - 1] + mtrx[maxi][j] + mtrx[maxi][j + 1] + mtrx[maxi][j - 1])))
        {
            mtrxelem = 1;
        }
        else {
            mtrxelem = 0;
        }
        
    }

    else if (i == maxi && j != maxj && j != 0) // нижняя грань матрицы
    {
        

        if (liveOrDie(mtrxelem, (mtrx[i][j + 1] + mtrx[i][j - 1] + mtrx[i - 1][j] + mtrx[i - 1][j + 1] + 
            mtrx[i - 1][j - 1] + mtrx[0][j] + mtrx[0][j + 1] + mtrx[0][j - 1])))
        {
            mtrxelem = 1;
        }
        else {
            mtrxelem = 0;
        }
    }

    else if (j == 0 && i != 0 && i != maxi) // левая грань
    {

        if (liveOrDie(mtrxelem, (mtrx[i - 1][j] + mtrx[i + 1][j] + mtrx[i][j + 1] + mtrx[i - 1][j + 1] + 
            mtrx[i + 1][j + 1] + mtrx[i][maxj] + mtrx[i + 1][maxj] + mtrx[i - 1][maxj])))
        {
            mtrxelem = 1;
        }
        else {
            mtrxelem = 0;
        }
    }

    else if (j == maxj && i != 0 && i != maxi) // правая грань
    {
        if (liveOrDie(mtrxelem, (mtrx[i - 1][j] + mtrx[i + 1][j] + mtrx[i][j - 1] + 
            mtrx[i - 1][j - 1] + mtrx[i + 1][j - 1] +
            mtrx[i][0] + mtrx[i + 1][0] + mtrx[i - 1][0]))){
            mtrxelem = 1;
        }
        else {
            mtrxelem = 0;
        }
    }
    else // внутренний элемент
    {
        if (liveOrDie(mtrxelem, (mtrx[i][j + 1] + mtrx[i][j - 1] + mtrx[i + 1][j] + mtrx[i - 1][j] + 
        mtrx[i + 1][j + 1] + mtrx[i - 1][j - 1] + mtrx[i - 1][j + 1] + mtrx[i + 1][j - 1]))){
            mtrxelem = 1;
        }
        else {
            mtrxelem = 0;
        }
    }
    return mtrxelem;
}

void matrixOuput(int**& mtrx, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mtrx[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}


int main(int argc, char* argv[])
{
    if (argc == 1) // вариант когда аргументов не передано, а значит мы рандомим матрицу
    {
        int m, n;
        std::cin >> m >> n;
        srand((unsigned)time(NULL));


        int** mtrx = new int* [m];

        for (int i = 0; i < m; i++)
        {
            mtrx[i] = new int[n];
            for (int j = 0; j < n; j++)
            {
                mtrx[i][j] = rand() % 2; // Рандомайзер

            }
        }
        


        while (true)
        {
            Sleep(1000);
            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    mtrx[i][j] = replace_mtrx(mtrx, mtrx[i][j], i, j, m - 1, n - 1);

                }
            }
            matrixOuput(mtrx, m, n);
        }

        for (int i = 0; i < m; i++)
            delete[] mtrx[i];
        delete[] mtrx;
        cout << endl;
        system("pause");
    }
    else if (argc == 2) // вариант когда аргумент передан, а значит мы читаем матрицу из файла
    {
        ifstream input(argv[1]);
        if (!input.is_open())
        {
            cout << "Cannot open file at \"" << argv[1] << "\"" << endl;
            system("pause");
            return 0;
        }
        else
        {
            
            int count = 0;
            int temp; 

            while (!input.eof())
            {
                input >> temp; 
                count++; 
            }

            input.clear();
            input.seekg(0, ios_base::beg);

            
            int count_space = 0;
            char symbol;
            while (!input.eof())
            {
                
                input.get(symbol);
                if (symbol == ' ') count_space++;
                if (symbol == '\n') break;
            }

            input.clear();
            input.seekg(0, ios_base::beg);

            int n = count / (count_space + 1);//число строк
            int m = count_space + 1;//число столбцов на единицу больше числа пробелов
            cout << n << endl << m << endl;
            int** mtrx;
            mtrx = new int* [n];
            for (int i = 0; i < n; i++) mtrx[i] = new int[m];

            // Считаем матрицу из файла
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    input >> mtrx[i][j];

            input.close();//под конец закроем файла
            matrixOuput(mtrx, n, m);
            while (true)
            {
                Sleep(1000);

                for (int i = 0; i < n; i++)
                    for (int j = 0; j < m; j++)
                        mtrx[i][j] = replace_mtrx(mtrx, mtrx[i][j], i, j, n - 1, m - 1);
                
                matrixOuput(mtrx, n, m);
            }
            for (int i = 0; i < n; i++) delete[] mtrx[i];
            delete[] mtrx;
        }
    }
    else 
    {
        cout << "Invalid amount of arguments, passed: " << argc - 1 << " expected 1 or 0." << endl;
        system("pause");
    }
    return 0;
}
