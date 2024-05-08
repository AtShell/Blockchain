
using System.Diagnostics;

class Programm
{
    static void Main(string[] args)
    {
        int a = 1000;
        int[,] m1 = new int[a, a];
        int[,] m2 = new int[a, a];
        int[,] m3 = new int[a, a];
        Stopwatch sw1 = new Stopwatch();
        Stopwatch sw2 = new Stopwatch();
        Stopwatch sw3 = new Stopwatch();
        m1 = inArr(m1);
        m2 = inArr(m2);
        sw1.Start();
        m3 = MylClass(m1, m2);
        sw1.Stop();
        TimeSpan ts1 = sw1.Elapsed;
        sw2.Start();
        m3 = MylNew(m1, m2);
        sw2.Stop();
        TimeSpan ts2 = sw2.Elapsed;
        sw3.Start();
        m3 = MylNew2(m1, m2);
        sw3.Stop();
        TimeSpan ts3 = sw3.Elapsed;
        Console.WriteLine("Классический вариант: " + ts1.ToString(@"m\:ss\.fff"));
        Console.WriteLine("Вариант с изменнымими индексами: " + ts2.ToString(@"m\:ss\.fff"));
        Console.WriteLine("Вариант с изменнымими индексами 2: " + ts3.ToString(@"m\:ss\.fff"));

    }
    static int[,] MylNew(int[,] arr1, int[,] arr2)
    {
        int[,] m3 = new int[arr1.GetLength(0), arr1.GetLength(1)];
        for (int i = 0; i < arr2.GetLength(0); i++)
        {
            for (int j = 0; j < arr2.GetLength(1); j++)
            {
                for (int k = 0; k < arr2.GetLength(0); k++)
                {
                    m3[i, j] += arr1[i, k] * arr2[k, j];
                }
            }
        }
        return m3;
    }
    static int[,] MylNew2(int[,] arr1, int[,] arr2)
    {
        int[,] m3 = new int[arr1.GetLength(0), arr1.GetLength(1)];
        for (int i = 0; i < arr2.GetLength(1); i++)
        {
            for (int j = 0; j < arr2.GetLength(0); j++)
            {
                for (int k = 0; k < arr2.GetLength(0); k++)
                {
                    m3[j, i] += arr1[j, k] * arr2[k, i];
                }
            }
        }
        return m3;
    }
    static int[,] MylClass(int[,] arr1, int[,] arr2)
    {
        int[,] m3 = new int[arr1.GetLength(0), arr1.GetLength(1)];
        for (int i = 0; i < arr2.GetLength(1); i++)
        {
            for (int j = 0; j < arr2.GetLength(0); j++)
            {
                for (int k = 0; k < arr2.GetLength(0); k++)
                {
                    m3[i, j] += arr1[i, k] * arr2[k, j];
                }
            }
        }
        return m3;
    }
    static int[,] inArr(int[,] arr)
    {
        for (int i = 0; i < arr.GetLength(0); i++)
        {
            for (int j = 0; j < arr.GetLength(1); j++)
            {
                arr[i, j] = (i + j) % 10 + 1;
            }
        }
        return arr;
    }
}