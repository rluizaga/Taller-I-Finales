/*
Escriba un programa que imprima por salida estándar los números entre 1 y 100, en orden
ascendente. Se pide que los números sean contabilizados por una variable global única y que
los pares sean escritos por un hilo mientras que los impares sean escritos por otro.
Contemple la correcta sincronización entre hilos y la liberación de los recursos utilizados.
*/

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int globalNumber = 1;

void printEvenNumbers()
{
    while (globalNumber <= 100)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (globalNumber % 2 == 0)
        {
            std::cout << "Even Thread: " << globalNumber << std::endl;
            globalNumber++;
        }
    }
}

void printOddNumbers()
{
    while (globalNumber < 100)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (globalNumber % 2 != 0)
        {
            std::cout << "Odd Thread: " << globalNumber << std::endl;
            globalNumber++;
        }
    }
}

int main()
{
    std::thread t1(printEvenNumbers);
    std::thread t2(printOddNumbers);

    t1.join();
    t2.join();

    return 0;
}
