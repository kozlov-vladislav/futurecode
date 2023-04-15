class Philosopher {
    Fork& LeftFork;
    Fork& RightFork;
public:
    Philosopher(Fork& left, Fork& right) : LeftFork(left), RightFork(right) {};

    void TakeAllForks() {
        if (LeftFork.GetNumber() < RightFork.GetNumber()) {
            LeftFork.TakeFork();
            RightFork.TakeFork();
        } else {
            RightFork.TakeFork();
            LeftFork.TakeFork();
        }
    }

    void RemoveAllForks() {
        LeftFork.RemoveFork();
        RightFork.RemoveFork();
    }
};