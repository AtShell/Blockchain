using System.Net.Sockets;
using System.Threading;
int y = 0;
object locker = new();
int x = 0;
Console.WriteLine("\nProblematic\n");
problematic();
Thread.Sleep(500);
Console.WriteLine("\nSolution\n");
solution();
void problematic()
{

    for (int i = 1; i < 6; i++)
    {
        Thread myThread = new(Print);
        myThread.Name = $"Thread {i}";
        myThread.Start();
    }
}
void solution()
{

    for (int i = 1; i < 6; i++)
    {
        Thread myThread = new(PrintLock);
        myThread.Name = $"Thread {i}";
        myThread.Start();
    }
}
void Print()
{
    x = 1;
    for (int i = 1; i < 6; i++)
    {
        Console.WriteLine($"{Thread.CurrentThread.Name}: {x}");
        x++;
    }
}
void PrintLock()
{
    lock (locker)
    {
        y = 1;
        for (int i = 1; i < 6; i++)
        {
            Console.WriteLine($"{Thread.CurrentThread.Name}: {y}");
            y++;
        }
    }
}
