///*** Petrovici Francesco-Gregorio, grupa 152 ***///
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <queue>
#include <cstdlib>
#include <algorithm>

#define NMAX 2000005

using namespace std;

vector <int> v;
vector <int> w;
vector <int> vsorted;

double get_exec_time(auto start, auto endd)
{
    double k = double(std::chrono::duration_cast <std::chrono::microseconds> (endd - start).count());
    //retunez in secunde
    //1 secunda = 10.000.000 microsecunde
    return k / 1000000.0;
}

void copy_vector (vector <int> source, vector <int> &destination)
{
    destination.clear();
    int n, i;
    n = source.size();
    for(i = 0; i < n; ++i)
        destination.push_back(source[i]);
}

bool vector_compare (vector <int> v1, vector <int> v2)
{
    int v1_len = v1.size();
    int v2_len = v2.size();
    if(v1_len != v2_len)
        return false;
    for(int i = 0; i < v1_len; ++i)
        if(v1[i] != v2[i])
            return false;
    return true;

}
///============================= Bubble Sort ================================///

void bubble_sort(vector <int> &v)
{
    bool sorted;
    int aux, i, n = v.size();
    //Protectie de timp, daca dureaza prea mult executia, aceasta va fi oprita automat
    auto start = std::chrono::steady_clock::now();
    do{
        sorted = true;
        auto extime = std::chrono::steady_clock::now();
        double elapsed_time = get_exec_time(start, extime);

        // 10 seconds

        if(elapsed_time > 60)
        {
            sorted = false;
            break;
        }
        for (i = 0; i < n - 1; ++i)
            if (v[i] > v[i + 1])
            {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
                sorted = false;
            }

    }while(!sorted);
    if(!sorted)
        cout << "Setul de date introdus nu poate fi sortat cu metoda bubble sort!" << endl;
}
///========= Sort cu priority Queue (un fel de Heap Sort?) ==========================//
void priority_sort(vector <int> &v)
{
    /*** Nu stiu daca chiar se numeste asa...eu l-am denumit priority sort pentru ca foloseste priority_queue***/
    int n = v.size(), i;
    priority_queue <int, vector <int>, greater <int> > sorted;
    for(i = 0; i < n; ++i)
        sorted.push(v[i]);
    v.clear();
    while(!sorted.empty())
    {
        v.push_back(sorted.top());
        sorted.pop();
    }
}

///======================================== Count Sort =======================================///
int k[NMAX];
void count_sort(vector <int> &v)
{
    bool is_sortable = true;
    int n = v.size(), maxx = -1, minn = NMAX, i, j;
    for(i = 0; i < n; ++i)
    {
        if(v[i] > NMAX - 1 || v[i] < 0)
        {
            is_sortable = false;
            break;
        }
        k[v[i]] ++;
        if(v[i] > maxx)
            maxx = v[i];
        if(v[i] < minn)
            minn = v[i];
    }
    if (is_sortable)
    {
        v.clear();
        for(i = minn; i <= maxx; ++i)
            for(j = 1; j <= k[i]; ++j)
                v.push_back(i);
    }
    else
        cout << "Setul de date introdus nu poate fi sortat folosind metoda count sort!" << endl;

}

///=============================== Quick Sort ===================================//

int get_partition(vector <int> &v, int left, int right, int pivot)
{
    while(left <= right)
    {
        while(v[left] < pivot)
            left ++;
        while(v[right] > pivot)
            right --;
        if(left <= right)
        {
            swap(v[left], v[right]);
            left ++;
            right --;
        }
    }
    return left;
}
void Qsort1(vector <int> &v, int left, int right)
{
    //bool sortable = true;
    auto start = std::chrono::steady_clock::now();
    if(left < right)
    {
        auto extime = std::chrono::steady_clock::now();
        double elapsed_time = get_exec_time(start, extime);

        //10 secunde

        if(elapsed_time > 10)
        {
            cout << "Quick sort cu pivot determinist a durat prea mult!" << '\n';
            return;
        }
        int pivot = v[(left + right) / 2];
        int index = get_partition(v, left, right, pivot);
        Qsort1(v, left, index - 1);
        Qsort1(v, index, right);
    }
    else
        return;
}

void Qsort2(vector <int> &v, int left, int right)
{
    //quick sort cu pivot random
    if(left < right)
    {
        int random = left + rand() % (right - left);
        int pivot = v[random];
        int index = get_partition(v, left, right, pivot);
        Qsort2(v, left, index - 1);
        Qsort2(v, index, right);
    }
    else
        return;
}

///============================= Merge Sort ================================///
//vector <int> temp;
void join(vector <int> &v, int left, int right)
{
    vector <int> temp;
    int mid = (left + right) / 2;
    int i = left, j = mid + 1;
    while(i <= mid && j <= right)
        if(v[i] < v[j])
            temp.push_back(v[i ++]);
        else
            temp.push_back(v[j ++]);
    while(i <= mid)
        temp.push_back(v[i ++]);
    while(j <= right)
        temp.push_back(v[j ++]);
    for(i = left; i <= right; ++i)
        v[i] = temp[i - left];
}
void merge_sort(vector <int> &v, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;
        merge_sort(v, left, mid);
        merge_sort(v, mid + 1, right);
        join(v, left, right);
    }
    else
        return;
}

///======================= Radix Sort ===========================///
void radix_sort(vector <int> &v)
{
    vector <int> aux[10];
    int p10 = 1;
    int i, ld;
    int n = v.size();
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (i = 0; i < n; ++i)
        {
            ld = (v[i] / p10) % 10;
            aux[ld].push_back(v[i]);
        }
        int poz = 0;
        for (auto &i:aux)
        {
            for (auto &j:i)
            {
                v[poz] = j;
                if (poz > 0 && v[poz] < v[poz - 1])
                    sorted = false;
                poz++;
            }
            i.clear();
        }
        p10 *= 10;
    }
}

int main()
{

    ifstream f("input.txt");
    ofstream g("output.txt");
    int i, t, n, x, j;
    double percentage = 0, increment;
    f >> t;
    increment = double(100 / t);
    for(i = 1; i <= t; i++)
    {
        //system("CLS");
        cout << "Va rugam sa asteptati...testele ruleaza: " << percentage <<" % " << '\n';
        v.clear();
        w.clear();
        vsorted.clear();
        double execution_time;
        g << "TESTUL " << i << '\n';
        f >> n;
        for(j = 0; j < n; ++ j)
        {
            f >> x;
            v.push_back(x);
            w.push_back(x);
            vsorted.push_back(x);
        }

        //copy_vector(v, w);
        ///=======sort din stl=======//

        auto start_time = std::chrono::steady_clock::now();
        sort(vsorted.begin(), vsorted.end());
        auto end_time = std::chrono::steady_clock::now();
        execution_time = get_exec_time(start_time, end_time);
        g << "Sort din stl: " << execution_time << " secunde" << '\n';
        cout << "Completed STL sort test " << i <<'\n';

        ///====== Bubble sort =========///

        start_time = std::chrono::steady_clock::now();
        bubble_sort(w);
        end_time = std::chrono::steady_clock::now();
        execution_time = get_exec_time(start_time, end_time);
        if(vector_compare(vsorted, w))
            g << "Bubble Sort: " << execution_time << '\n';
        else
             g << "Bubble Sort nu poate sorta" << '\n';
        cout << "Completed bubble sort test " << i <<'\n';

        ///===== Sort cu priority queue ========///

        copy_vector(v, w);
        start_time = std::chrono::steady_clock::now();
        priority_sort(w);
        end_time = std::chrono::steady_clock::now();
        execution_time = get_exec_time(start_time, end_time);
        if(vector_compare(vsorted, w))
            g << "Priority sort: " << execution_time << " secunde." << '\n';
        else
             g << "Priority Sort nu poate sorta" << '\n';
        cout << "Completed priority sort test " << i <<'\n';

        ///=================== Count Sort ============================///

        copy_vector(v, w);
        start_time = std::chrono::steady_clock::now();
        count_sort(w);
        end_time = std::chrono::steady_clock::now();
        execution_time = get_exec_time(start_time, end_time);
        if(vector_compare(vsorted, w))
            g << "Count sort: " << execution_time << " secunde." << '\n';
        else
             g << "Count Sort nu poate sorta" << '\n';
        cout << "Completed count sort test " << i <<'\n';

        ///============ Quick sort cu pivot in mijloc ================///

        copy_vector(v, w);
        start_time = std::chrono::steady_clock::now();
        Qsort1(w, 0, n - 1);
        end_time = std::chrono::steady_clock::now();
        execution_time = get_exec_time(start_time, end_time);
        if(vector_compare(vsorted, w))
            g << "Quick sort cu pivot determinist (in mijloc): " << execution_time << " secunde." << '\n';
        else
             g << "Quick sort cu pivot determinist (in mijloc) nu poate sorta!" << '\n';
        cout << "Completed quick sort determinist test " << i <<'\n';

        ///============ Quick sort cu pivot randomizat ================///

        copy_vector(v, w);
        start_time = std::chrono::steady_clock::now();
        Qsort2(w, 0, n - 1);
        end_time = std::chrono::steady_clock::now();
        execution_time = get_exec_time(start_time, end_time);
        if(vector_compare(vsorted, w))
            g << "Quick sort cu pivot randomizat: " << execution_time << " secunde." << '\n';
        else
             g << "Quick sort cu pivot randomizat nu poate sorta!" << '\n';
        cout << "Completed quick sort random test " << i <<'\n';

        ///============ Merge Sort ================///

        copy_vector(v, w);
        start_time = std::chrono::steady_clock::now();
        merge_sort(w, 0, n - 1);
        end_time = std::chrono::steady_clock::now();
        execution_time = get_exec_time(start_time, end_time);
        if(vector_compare(vsorted, w))
            g << "Merge sort: " << execution_time << " secunde." << '\n';
        else
             g << "Merge sort nu poate sorta!" << '\n';
        cout << "Completed merge sort test " << i <<'\n';

        ///============ Radix Sort ================///

        copy_vector(v, w);
        start_time = std::chrono::steady_clock::now();
        radix_sort(w);
        end_time = std::chrono::steady_clock::now();
        execution_time = get_exec_time(start_time, end_time);
        if(vector_compare(vsorted, w))
            g << "Radix sort: " << execution_time << " secunde." << '\n';
        else
             g << "Radix sort nu poate sorta!" << '\n';
        g << '\n';
        cout << "Completed radix sort test " << i <<'\n';
        percentage += increment;
        //resetare vector pt countsort
        for(int l = 0; l < NMAX; ++l)
            k[l] = 0;

    }
    //system("CLS");
    cout << "Programul a rulat cu succes, va rugam sa verificati fisierul output.txt pentru a vedea rezultatele!";
    return 0;
}
