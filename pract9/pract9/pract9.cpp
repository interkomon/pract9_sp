// pract9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>



double methodLaplass(DOUBLE matrix[3][3],int n)
{
    //использую метод лапласса
    double lap = 0;
    double submatrix[3][3];
    if (n == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            lap = lap + (pow(-1, x) * matrix[0][x] * methodLaplass(submatrix, n - 1));
        }
    }
    return lap;
}

DWORD WINAPI CalculatingDetermiant(LPVOID data) {
    double(*matrix)[3] = (double(*)[3])data;
    double opr = methodLaplass(matrix, 3);
    std::cout << "Определитель матрицы: " << opr << std::endl;
    Sleep(100);
    return 0;
}


int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Hello World!\n";

    double matrix1[3][3] = { {5,8,7},{3,5,6},{5,5,6} };
    double matrix2[3][3] = { {1,2,3},{4,5,6}, {7,8,9} };
    HANDLE hThread[2];
    hThread[0] = CreateThread(NULL, 0, CalculatingDetermiant, matrix1, 0, NULL);
   

    if (hThread[0] == NULL)
    {
        return GetLastError();
    }
    WaitForSingleObject(hThread[0], INFINITE);
    CloseHandle(hThread[0]);

    hThread[1] = CreateThread(NULL, 0, CalculatingDetermiant, matrix2, 0, NULL);
    if (hThread[1] == NULL)
    {
        return GetLastError();
    }
    
    WaitForSingleObject(hThread[1], INFINITE);
         
    CloseHandle(hThread[1]);

    return 0;
    
}








// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
