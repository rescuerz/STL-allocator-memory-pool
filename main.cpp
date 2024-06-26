#include <iostream>
#include <random>
#include <vector>
#include "MyAllocator.cpp"
#include <ctime>
// include header of your allocator here

template<class T>
using STLAlloc = std::allocator<T>; // replace the std::allocator with your allocator
template<class T>
using MyAlloc = MyAllocator<T>;
using Point2D = std::pair<int, int>;
const int TestSize = 64;
const int PickSize = 1000;



double testMy(int iteration) {
    clock_t start,end;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);


    start = clock();
    for(int u = 0; u < iteration; u++) {
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
        for (int i = 0; i < PickSize; i++) {
            int idx = dis(gen) - 1;
            int size = dis(gen);
            vecints[idx].resize(size);
            vecpts[idx].resize(size);
        }
        int c1 = 0, c2 = 0;
        for (int i = 0; i < PickSize; i++) {
            int val = 10;
            int idx1 = dis(gen) - 1;
            int idx2 = vecints[idx1].size() / 2;
            vecints[idx1][idx2] = val;
            if (vecints[idx1][idx2] == val)
                c1++;
        }
        for (int i = 0; i < PickSize; i++) {
            Point2D val(11, 15);
            int idx1 = dis(gen) - 1;
            int idx2 = vecpts[idx1].size() / 2;
            vecpts[idx1][idx2] = val;
            if (vecpts[idx1][idx2] == val)
                c2++;
        }
        std::cout << "Correct insertion in vecint :"<<c1 <<std::endl;
        std::cout << "Incorrect insertion in vecint :"<<PickSize- c1 <<std::endl;
        std::cout << "Correct insertion in vecint :"<<c2 <<std::endl;
        std::cout << "Incorrect insertion in vecint :"<<PickSize- c2 <<std::endl;
        for (auto i = 0; i < vecints.size(); i++) {
            vecints.pop_back();
        }
        for (auto i = 0; i < vecpts.size(); i++) {
            vecpts.pop_back();
        }

        std::vector<IntVec, MyAlloc<IntVec>> vecints2(TestSize);

        std::vector<PointVec, MyAlloc<PointVec>> vecpts2(TestSize);
        int p1 = 0, p2= 0;
        for (int i = 0; i < PickSize; i++) {
            int idx1 = dis(gen) - 1;
            vecints2[idx1].push_back(i);
            if (vecints2[idx1].back() == i)
                p1++;
        }
        for (int i = 0; i < PickSize; i++) {
            int idx1 = dis(gen) - 1;
            vecpts2[idx1].push_back(Point2D(i,i));
            if (vecpts2[idx1].back() == Point2D(i,i))
                p2++;
        }
        std::cout << "Correct push_back in vecint :"<<p1 <<std::endl;
        std::cout << "Incorrect push_back in vecint :"<<PickSize- p1 <<std::endl;
        std::cout << "Correct push_back in vecint :"<<p2 <<std::endl;
        std::cout << "Incorrect push_back in vecint :"<<PickSize- p2 <<std::endl;
    }
    end = clock();
    return (end*1.0-start*1.0)/iteration*1.0;
};

double testSTL(int iteration) {

    clock_t start,end;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);


    start = clock();
    for(int u = 0; u < iteration; u++) {
        // vector creation
        using IntVec = std::vector<int, STLAlloc<int>>;
        std::vector<IntVec, STLAlloc<IntVec>> vecints(TestSize);
        for (int i = 0; i < TestSize; i++)
            vecints[i].resize(dis(gen));

        using PointVec = std::vector<Point2D, STLAlloc<Point2D>>;
        std::vector<PointVec, STLAlloc<PointVec>> vecpts(TestSize);
        for (int i = 0; i < TestSize; i++)
            vecpts[i].resize(dis(gen));

        // vector resize
        for (int i = 0; i < PickSize; i++) {
            int idx = dis(gen) - 1;
            int size = dis(gen);
            vecints[idx].resize(size);
            vecpts[idx].resize(size);
        }
        int c1 = 0, c2 = 0;
        for (int i = 0; i < PickSize; i++) {
            int val = 10;
            int idx1 = dis(gen) - 1;
            int idx2 = vecints[idx1].size() / 2;
            vecints[idx1][idx2] = val;
            if (vecints[idx1][idx2] == val)
                c1++;
        }
        for (int i = 0; i < PickSize; i++) {
            Point2D val(11, 15);
            int idx1 = dis(gen) - 1;
            int idx2 = vecpts[idx1].size() / 2;
            vecpts[idx1][idx2] = val;
            if (vecpts[idx1][idx2] == val)
                c2++;
        }
        std::cout << "Correct insertion in vecint :"<<c1 <<std::endl;
        std::cout << "Incorrect insertion in vecint :"<<PickSize- c1 <<std::endl;
        std::cout << "Correct insertion in vecint :"<<c2 <<std::endl;
        std::cout << "Incorrect insertion in vecint :"<<PickSize- c2 <<std::endl;
        for (auto i = 0; i < vecints.size(); i++) {
            vecints.pop_back();
        }
        for (auto i = 0; i < vecpts.size(); i++) {
            vecpts.pop_back();
        }

        std::vector<IntVec, STLAlloc<IntVec>> vecints2(TestSize);

        std::vector<PointVec, STLAlloc<PointVec>> vecpts2(TestSize);
        int p1 = 0, p2= 0;
        for (int i = 0; i < PickSize; i++) {
            int idx1 = dis(gen) - 1;
            vecints2[idx1].push_back(i);
            if (vecints2[idx1].back() == i)
                p1++;
        }
        for (int i = 0; i < PickSize; i++) {
            int idx1 = dis(gen) - 1;
            vecpts2[idx1].push_back(Point2D(i,i));
            if (vecpts2[idx1].back() == Point2D(i,i))
                p2++;
        }
        std::cout << "Correct push_back in vecint :"<<p1 <<std::endl;
        std::cout << "Incorrect push_back in vecint :"<<PickSize- p1 <<std::endl;
        std::cout << "Correct push_back in vecint :"<<p2 <<std::endl;
        std::cout << "Incorrect push_back in vecint :"<<PickSize- p2 <<std::endl;
    }
    end = clock();
    return (end*1.0-start*1.0)/iteration*1.0;
};

int main()
{
    double mytime = testMy(100000);
    double stltime = testSTL(100000);
    std::cout << "[MyAllocator] Average Time " <<mytime << std::endl;
    std::cout << "[STLAllocator] Average Time " << stltime << std::endl;
    return 0;
}