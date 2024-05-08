using static System.Console;


var lock1 = new object();
var lock2 = new object();

void Lock1()
{
    var threadId = Thread.CurrentThread.ManagedThreadId;

    lock (lock1)
    {
        WriteLine($"Поток {threadId} получил блокировку 1.");
        Thread.Sleep(1000);
        WriteLine($"Поток {threadId} попытался получить блокировку 2.");
        lock (lock2)
        {
            WriteLine($"Поток {threadId} получил блокировку 2.");
        }
    }
}

void Lock2()
{
    var threadId = Thread.CurrentThread.ManagedThreadId;

    lock (lock2)
    {
        WriteLine($"Поток {threadId} получил блокировку 2.");
        Thread.Sleep(1000);
        WriteLine($"Поток {threadId} попытался получить блокировку 1.");
        lock (lock1)
        {
            WriteLine($"Поток {threadId} получил блокировку 1.");
        }
    }
}

var thread1 = new Thread(Lock1);
var thread2 = new Thread(Lock2);

thread1.Start();
thread2.Start();

thread1.Join();
thread2.Join();

ReadLine();

//using static System.Console;

//var lock1 = new object();
//var lock2 = new object();

//void Lock1()
//{
//    var threadId = Thread.CurrentThread.ManagedThreadId;

//    while (true)
//    {
//        if (Monitor.TryEnter(lock1, TimeSpan.FromSeconds(1)))
//        {
//            try
//            {
//                WriteLine($"Поток {threadId} получил блокировку 1.");
//                Thread.Sleep(1000);
//                WriteLine($"Поток {threadId} попытался получить блокировку 2.");

//                if (Monitor.TryEnter(lock2, TimeSpan.FromSeconds(1)))
//                {
//                    try
//                    {
//                        WriteLine($"Поток {threadId} получил блокировку 2.");
//                        break;
//                    }
//                    finally
//                    {
//                        Monitor.Exit(lock2);
//                    }
//                }
//            }
//            finally
//            {
//                Monitor.Exit(lock1);
//            }
//        }
//    }

//    WriteLine($"Поток {threadId} завершен");
//}

//void Lock2()
//{
//    var threadId = Thread.CurrentThread.ManagedThreadId;

//    while (true)
//    {
//        if (Monitor.TryEnter(lock2, TimeSpan.FromSeconds(1)))
//        {
//            try
//            {
//                WriteLine($"ПОток {threadId} получил блокировку 2.");
//                Thread.Sleep(1000);
//                WriteLine($"Поток {threadId} попытался получить блокировку 1.");

//                if (Monitor.TryEnter(lock1, TimeSpan.FromSeconds(1)))
//                {
//                    try
//                    {
//                        WriteLine($"Поток {threadId} получил блокировку 1.");
//                        break;
//                    }
//                    finally
//                    {
//                        Monitor.Exit(lock1);
//                    }
//                }
//            }
//            finally
//            {
//                Monitor.Exit(lock2);
//            }
//        }
//    }

//    WriteLine($"Поток {threadId} завершен");
//}

//var thread1 = new Thread(Lock1);
//var thread2 = new Thread(Lock2);

//thread1.Start();
//thread2.Start();

//thread1.Join();
//thread2.Join();

//ReadLine();