

void MakePhilosopherEat(Philosopher& philosopher) {
    philosopher.TakeAllForks();
    philosopher.RemoveAllForks();
}

void testN(int n, int m) {
    std::vector<Fork> forks(n);
    for (int i = 0; i < n; ++i) {
        forks[i].SetNumber(i);
    }
    std::vector<std::thread> threads;
    threads.reserve(n);

    for (int i = 0; i < n; ++i) {
        threads.emplace_back([&](int number) {
            Philosopher philosopher(forks[number], forks[(number + 1) % n]);
            for (int j = 0; j < m; ++j) {
                MakePhilosopherEat(philosopher);
            }
        }, i);
    }

    for (auto& th : threads) {
        th.join();
    }

    for (auto& f : forks) {
        assert(f.GetCounter1() == f.GetCounter2());
        assert(f.GetCounter1() >= m);
    }
}

int main() {
    testN(2, 100);
    testN(3, 10);
    testN(3, 100);
    testN(3, 10000);
    testN(4, 100);
    testN(100, 1000);
