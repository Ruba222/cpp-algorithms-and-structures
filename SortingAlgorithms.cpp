#include <bits/stdc++.h>
#include <chrono> // For timing
#include <string>
using namespace std;
using namespace std::chrono;

class student {
public:
    student() {

    }

    string name;
    string id;
    double GPA;


    // Constructor
    student(string n, string i, double g) {
        name = n;
        id = i;
        GPA = g;
    }

    bool operator<(const student& other) const {
        return name < other.name;
    }
    bool operator > (const student& other) const {
        return GPA < other.GPA;
    }

    void display() const {
    }
};


// Function to write sorted student elements on a file
template<typename T>
void writeSortedInfo(const vector<T>& arr, const string& algorithm, double duration, const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    outputFile << "Algorithm: " << algorithm << endl;
    outputFile << "Running Time: " << duration << " microseconds" << endl;
    // Write to file
    for (const auto& elem : arr) {
        outputFile << elem.name << " \n" << elem.id << " \n"<<elem.GPA<<"\n";
    }
    outputFile.close();
}

//by GPA:
template<typename T>
void InsertionSortG(vector<T>&  arr){
    for(int i=1,j;i<arr.size();i++){
        T k=arr[i];
        for(j=i;j>0 && arr[j-1]>k;j--){
            arr[j]=arr[j-1];
        }
        arr[j]=k;
    }
}

template<typename T>
void SelectionSortG(vector<T>& arr){
    for(int i=0;i<arr.size();i++){
        for(int j=i+1;j<arr.size();j++){
            if(arr[i]>arr[j]){
                swap(arr[i],arr[j]);
            }
        }

    }
}

template<typename T>
void BubbleSortG(vector<T>& arr){
    bool g= true;
    for(int i=0;i<(arr.size())-1;i++){
        for(int j=i+1;j<arr.size();j++){
            if(arr[i]>arr[j]){

                swap(arr[j],arr[i]);
                g= false;
            }
        }
        if(g== true){

            break;
        }

    }
}

template<typename T>
void ShellSortG(vector<T>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap &&   arr[j - gap]>temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

template<typename T>
void MergeG(vector<T>& arr, int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    vector<T> tempArr(r - l + 1);

    while (i <= m && j <= r) {
        if (arr[j]>arr[i]) {
            tempArr[k++] = arr[i++];
        } else {
            tempArr[k++] = arr[j++];
        }
    }

    while (i <= m) {
        tempArr[k++] = arr[i++];
    }
    while (j <= r) {
        tempArr[k++] = arr[j++];
    }

    for (int y = l; y <= r; y++) {
        arr[y] = tempArr[y - l];
    }
}

template<typename T>
void MergeSortG(vector<T>& arr, int l, int r) {
    if (r > l) {
        int m = l + (r - l) / 2;
        MergeSortG(arr, l, m);
        MergeSortG(arr, m + 1, r);
        MergeG(arr, l, m, r);
    }
}

template<typename T>
int  partitionG(vector<T>& arr,int l,int r){
    int i=l,j;
    T x=arr[l];
    for(j=i+1;j<=r;j++){
        if(x>arr[j]){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i],arr[l]);
    return i;
}

template<typename T>
void QuickSortG(vector<T>& arr,int l,int r){
    if(l<r){

        int mid=  partitionG(arr,l,r);
        QuickSortG(arr,l,mid-1);
        QuickSortG(arr,mid+1,r);
    }
}
//by name
template<typename T>
void InsertionSort(vector<T>& arr) {
    for (int i = 1, j; i < arr.size(); i++) {
        T k = arr[i];
        for (j = i; j > 0 && k < arr[j - 1]; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = k;
    }
}

template<typename T>
void SelectionSort(vector<T>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[i]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

template<typename T>
void BubbleSort(vector<T>& arr) {
    bool g = true;
    for (int i = 0; i < (arr.size()) - 1; i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[i]) {
                swap(arr[j], arr[i]);
                g = false;
            }
        }
        if (g == true) {
            break;
        }
    }
}

template<typename T>
void ShellSort(vector<T>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && temp < arr[j - gap]; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

template<typename T>
void MergeN(vector<T>& arr, int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    vector<T> tempArr(r - l + 1);

    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) {
            tempArr[k++] = arr[i++];
        } else {
            tempArr[k++] = arr[j++];
        }
    }

    while (i <= m) {
        tempArr[k++] = arr[i++];
    }
    while (j <= r) {
        tempArr[k++] = arr[j++];
    }

    for (int y = l; y <= r; y++) {
        arr[y] = tempArr[y - l];
    }
}

template<typename T>
void MergeSort(vector<T>& arr, int l, int r) {
    if (r > l) {
        int m = l + (r - l) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        MergeN(arr, l, m, r);
    }
}

template<typename T>
int partitionN(vector<T>& arr, int l, int r) {
    int i = l, j;
    T x = arr[l];
    for (j = i + 1; j <= r; j++) {
        if (arr[j] < x) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i], arr[l]);
    return i;
}

template<typename T>
void QuickSort(vector<T>& arr, int l, int r) {
    if (l < r) {
        int mid = partitionN(arr, l, r);
        QuickSort(arr, l, mid - 1);
        QuickSort(arr, mid + 1, r);
    }
}

template<typename T>
double measureSortingTime(void (*sortingFunction)(vector<T>&), vector<T>& arr) {
    auto start = steady_clock::now();
    sortingFunction(arr);
    auto stop = steady_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}
//for quick/merge
template<typename T>
double measureSortingTime2(void (*sortingFunction)(vector<T>&, int, int), vector<T>& arr, int l, int r) {
    auto start = steady_clock::now();
    sortingFunction(arr, l, r);
    auto stop = steady_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}
int main() {
    ifstream file("students.txt");
    if (!file) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    int numStudents;
    file >> numStudents;

    vector<student> students;

    for (int i = 0; i < numStudents; ++i) {
        string name;
        string id;
        double gpa;
        file.ignore(); // ignore newline character
        getline(file, name);
        file >> id >> gpa;
        students.push_back(student(name, id, gpa));
    }

    file.close();

    cout << "Select the number of the algorithm you want to use \n";
    cout<<"1.Insertion Sort\n"<<"2.Selection Sort\n"<<"3.Bubble Sort\n";
    cout<<"4.Shell Sort\n"<<"5.Merge Sort\n"<<"6.Quick Sort\n";
    string algorithm;
    int num;
    cin>>num;
    switch (num) {
        case 1: {
            algorithm = "InsertionSort";
            double duration = measureSortingTime(InsertionSort<student>, students);
            writeSortedInfo(students, algorithm, duration, "SortedByName.txt");
            duration = measureSortingTime(InsertionSortG<student>, students);
            writeSortedInfo(students, algorithm, duration, "SortedByGPA.txt");
            cout<<"Insertion Sort Successful check output files"<<endl;

        }
            break;



        case 2:{
                algorithm ="SelectionSort";
                double duration = measureSortingTime(SelectionSort<student>, students);
                writeSortedInfo(students, algorithm, duration, "SortedByName.txt");
                //by gpa
                duration = measureSortingTime(SelectionSortG < student >, students);
                writeSortedInfo(students, algorithm, duration, "SortedByGPA.txt");
            cout<<"Selection Sort Successful check output files"<<endl;

        }
        break;


        case 3:{
                algorithm = "BubbleSort";
                double duration = measureSortingTime(BubbleSort<student>, students);
                writeSortedInfo(students, algorithm, duration, "SortedByName.txt");
                duration = measureSortingTime(BubbleSortG<student>, students);
                writeSortedInfo(students, algorithm, duration, "SortedByGPA.txt");
                cout<<"Bubble Sort Successful check output files"<<endl;

        }
        break;


        case 4:{
                algorithm = "ShellSort";
                double duration = measureSortingTime(ShellSort<student>, students);
                writeSortedInfo(students, algorithm, duration, "SortedByName.txt");
                duration = measureSortingTime(ShellSortG<student>, students);
                writeSortedInfo(students, algorithm, duration, "SortedByGPA.txt");
                cout<<"Shell Sort Successful check output files"<<endl;

        }
        break;


        case 5:{
                algorithm = "MergeSort";
                double duration = measureSortingTime2(MergeSort<student>, students, 0, students.size() - 1);
                writeSortedInfo(students, algorithm, duration, "SortedByName.txt");
                duration = measureSortingTime2(MergeSortG<student>, students, 0, students.size() - 1);
                writeSortedInfo(students, algorithm, duration, "SortedByGPA.txt");
                cout<<"Merge Sort Successful check output files"<<endl;

        }
        break;

            case 6:{
                    algorithm = "QuickSort";
                    double duration = measureSortingTime2(QuickSort<student>, students, 0, students.size() - 1);
                    writeSortedInfo(students, algorithm, duration, "SortedByName.txt");
                    duration = measureSortingTime2(QuickSort<student>, students, 0, students.size() - 1);
                    writeSortedInfo(students, algorithm, duration, "SortedByGPA.txt");
                    cout<<"Quick Sort Successful check output files"<<endl;

            }
            break;

        default:{
            cout<<"Please enter a valid number from the list above"<<endl;
        }
        break;

    }

    return 0;
}