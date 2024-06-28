#include "MyAllocator.cpp"

// include header of your allocator here

template <class T>
using STLAlloc = std::allocator<T>; // replace the std::allocator with your allocator
template <class T>
using MyAlloc = MyAllocator<T>;

using Point2D = std::pair<int, int>;
const int TestSize = 10000;
const int PickSize = 1000;

double MyAlloc_test(int iteration, double *total_time)
{
    clock_t start_clock, end_clock;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);

    start_clock = clock();
    for (int i = 0; i < iteration; i++)
    {
        // vector creation
        using IntVec = std::vector<int, MyAlloc<int>>;
        std::vector<IntVec, MyAlloc<IntVec>> vecints(TestSize);
        for (int i = 0; i < TestSize; i++)
            vecints[i].resize(dis(gen));

        using PointVec = std::vector<Point2D, MyAlloc<Point2D>>;
        std::vector<PointVec, MyAlloc<PointVec>> vecpts(TestSize);
        for (int i = 0; i < TestSize; i++)
            vecpts[i].resize(dis(gen));

        // vector resize
        for (int i = 0; i < PickSize; i++)
        {
            int idx = dis(gen) - 1;
            int size = dis(gen);
            vecints[idx].resize(size);
            vecpts[idx].resize(size);
        }
        // vector element assignment
        int correct_num = 0;
        int incorrect_num = 0;
        for (int i = 0; i < PickSize; i++)
        {
            int val = 10;
            int idx1 = dis(gen) - 1;
            int idx2 = vecints[idx1].size() / 2;
            vecints[idx1][idx2] = val;
            if (vecints[idx1][idx2] == val)
                correct_num++;
            else
                incorrect_num++;
        }
        std::cout << "Correct insertion in vecint :" << correct_num << std::endl;
        std::cout << "Incorrect insertion in vecint :" << incorrect_num << std::endl;
        correct_num = 0;
        incorrect_num = 0;
        for (int i = 0; i < PickSize; i++)
        {
            Point2D val(11, 15);
            int idx1 = dis(gen) - 1;
            int idx2 = vecpts[idx1].size() / 2;
            vecpts[idx1][idx2] = val;
            if (vecpts[idx1][idx2] == val)
                correct_num++;
            else
                incorrect_num++;
        }

        std::cout << "Correct insertion in vecint :" << correct_num << std::endl;
        std::cout << "Incorrect insertion in vecint :" << incorrect_num << std::endl;

        // vector pop_back
        for (auto i = 0; i < vecints.size(); i++)
        {
            vecints.pop_back();
        }
        for (auto i = 0; i < vecpts.size(); i++)
        {
            vecpts.pop_back();
        }

        std::vector<IntVec, MyAlloc<IntVec>> vecints2(TestSize);

        std::vector<PointVec, MyAlloc<PointVec>> vecpts2(TestSize);
        correct_num = incorrect_num = 0;
        for (int i = 0; i < PickSize; i++)
        {
            int idx1 = dis(gen) - 1;
            vecints2[idx1].push_back(i);
            if (vecints2[idx1].back() == i)
                correct_num++;
            else
                incorrect_num++;
        }
        std::cout << "Correct push_back in vecint :" << correct_num << std::endl;
        std::cout << "Incorrect push_back in vecint :" << incorrect_num << std::endl;
        correct_num = incorrect_num = 0;
        for (int i = 0; i < PickSize; i++)
        {
            int idx1 = dis(gen) - 1;
            vecpts2[idx1].push_back(Point2D(i, i));
            if (vecpts2[idx1].back() == Point2D(i, i))
                correct_num++;
            else
                incorrect_num++;
        }

        std::cout << "Correct push_back in vecint :" << correct_num << std::endl;
        std::cout << "Incorrect push_back in vecint :" << incorrect_num << std::endl;
    }
    end_clock = clock();
    // 将时间转化为秒
    *total_time = (end_clock * 1.0 - start_clock * 1.0) / CLOCKS_PER_SEC;
    return (end_clock * 1.0 - start_clock * 1.0) / iteration * 1.0 / CLOCKS_PER_SEC;
};

double STL_test(int iteration, double *total_time)
{

    clock_t start_clock, end_clock;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);

    start_clock = clock();
    for (int i = 0; i < iteration; i++)
    {
        // vector creation
        using IntVec = std::vector<int, MyAlloc<int>>;
        std::vector<IntVec, MyAlloc<IntVec>> vecints(TestSize);
        for (int i = 0; i < TestSize; i++)
            vecints[i].resize(dis(gen));

        using PointVec = std::vector<Point2D, MyAlloc<Point2D>>;
        std::vector<PointVec, MyAlloc<PointVec>> vecpts(TestSize);
        for (int i = 0; i < TestSize; i++)
            vecpts[i].resize(dis(gen));

        // vector resize
        for (int i = 0; i < PickSize; i++)
        {
            int idx = dis(gen) - 1;
            int size = dis(gen);
            vecints[idx].resize(size);
            vecpts[idx].resize(size);
        }
        // vector element assignment
        int correct_num = 0;
        int incorrect_num = 0;
        for (int i = 0; i < PickSize; i++)
        {
            int val = 10;
            int idx1 = dis(gen) - 1;
            int idx2 = vecints[idx1].size() / 2;
            vecints[idx1][idx2] = val;
            if (vecints[idx1][idx2] == val)
                correct_num++;
            else
                incorrect_num++;
        }
        std::cout << "Correct insertion in vecint :" << correct_num << std::endl;
        std::cout << "Incorrect insertion in vecint :" << incorrect_num << std::endl;
        correct_num = 0;
        incorrect_num = 0;
        for (int i = 0; i < PickSize; i++)
        {
            Point2D val(11, 15);
            int idx1 = dis(gen) - 1;
            int idx2 = vecpts[idx1].size() / 2;
            vecpts[idx1][idx2] = val;
            if (vecpts[idx1][idx2] == val)
                correct_num++;
            else
                incorrect_num++;
        }

        std::cout << "Correct insertion in vecint :" << correct_num << std::endl;
        std::cout << "Incorrect insertion in vecint :" << incorrect_num << std::endl;

        // vector pop_back
        for (auto i = 0; i < vecints.size(); i++)
        {
            vecints.pop_back();
        }
        for (auto i = 0; i < vecpts.size(); i++)
        {
            vecpts.pop_back();
        }

        std::vector<IntVec, MyAlloc<IntVec>> vecints2(TestSize);

        std::vector<PointVec, MyAlloc<PointVec>> vecpts2(TestSize);
        correct_num = incorrect_num = 0;
        for (int i = 0; i < PickSize; i++)
        {
            int idx1 = dis(gen) - 1;
            vecints2[idx1].push_back(i);
            if (vecints2[idx1].back() == i)
                correct_num++;
            else
                incorrect_num++;
        }
        std::cout << "Correct push_back in vecint :" << correct_num << std::endl;
        std::cout << "Incorrect push_back in vecint :" << incorrect_num << std::endl;
        correct_num = incorrect_num = 0;
        for (int i = 0; i < PickSize; i++)
        {
            int idx1 = dis(gen) - 1;
            vecpts2[idx1].push_back(Point2D(i, i));
            if (vecpts2[idx1].back() == Point2D(i, i))
                correct_num++;
            else
                incorrect_num++;
        }

        std::cout << "Correct push_back in vecint :" << correct_num << std::endl;
        std::cout << "Incorrect push_back in vecint :" << incorrect_num << std::endl;
    }
    end_clock = clock();
    *total_time = (end_clock * 1.0 - start_clock * 1.0) / CLOCKS_PER_SEC;
    return (end_clock * 1.0 - start_clock * 1.0) / iteration * 1.0 / CLOCKS_PER_SEC;
};

int main()
{
    double my_total_time, stl_total_time;
    double mytime = MyAlloc_test(100, &my_total_time);
    double stltime = STL_test(100, &stl_total_time);
    std::cout << "[MyAllocator] Total time " << my_total_time << std::endl;
    std::cout << "[STLAllocator] Total time " << stl_total_time << std::endl;
    std::cout << "[MyAllocator] Average Time " << mytime << std::endl;
    std::cout << "[STLAllocator] Average Time " << stltime << std::endl;
    return 0;
}