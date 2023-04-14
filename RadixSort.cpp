#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool is_sorted(const vector<string>& arr);
void counting_sort(vector<string>& arr, int index);
void radix_sort(vector<string>& arr);
vector<string> generate_random_strings(int n, int length);
void print_strings(const vector<string>& arr);

int main() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));

    // Тестирование среднего случая
    vector<string> test_case = generate_random_strings(5, 5);
    auto start = high_resolution_clock::now();
    radix_sort(test_case);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    if (is_sorted(test_case)) {
        cout << "Medium case: successful\n";
        print_strings(test_case);
        cout << "Time taken: " << duration.count() << " ms\n\n";
    }
    else {
        cout << "Medium case: failed\n";
    }

    // Тестирование худшего случая
    vector<string> worst_case = { "orange", "lemon", "grape", "banana", "apple" };
    start = high_resolution_clock::now();
    radix_sort(worst_case);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    if (is_sorted(worst_case)) {
        cout << "Worst case: successful\n";
        print_strings(worst_case);
        cout << "Time taken: " << duration.count() << " ms\n\n";
    }
    else {
        cout << "Worst case: failed\n";
    }

    // Тестирование лучшего случая
    vector<string> best_case = { "apple", "banana", "grape", "lemon", "orange" };
    start = high_resolution_clock::now();
    radix_sort(best_case);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    if (is_sorted(best_case)) {
        cout << "Best case: successful\n";
        print_strings(best_case);
        cout << "Time taken: " << duration.count() << " ms\n\n";
    }
    else {
        cout << "Best case: failed\n";
    }

    return 0;
}



// Функция проверки упорядоченности массива строк
bool is_sorted(const vector<string>& arr)
{
    for (size_t i = 1; i < arr.size(); i++) {
        // Если текущий элемент меньше предыдущего, последовательность не упорядочена
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// Функция сортировки подсчетом для одного разряда
void counting_sort(vector<string>& arr, int index)
{
    int n = arr.size();
    vector<string> output(n);
    vector<int> count(26, 0);

    // Подсчет количества строк с каждой буквой в данном разряде
    for (int i = 0; i < n; i++) {
        count[arr[i][index] - 'a']++;
    }

    // Вычисление префиксных сумм для массива count
    for (int i = 1; i < 26; i++) {
        count[i] += count[i - 1];
    }

    // Заполнение выходного массива в соответствии с префиксными суммами
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i][index] - 'a'] - 1] = arr[i];
        count[arr[i][index] - 'a']--;
    }

    // Копирование отсортированных элементов из выходного массива в исходный
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Функция поразрядной сортировки для массива строк
void radix_sort(vector<string>& arr)
{
    // Нахождение максимальной длины строки в массиве
    int max_length = arr[0].size();
    for (const string& s : arr) {
        max_length = max(max_length, static_cast<int>(s.size()));
    }

    // Дополнение строк символом 'a' до максимальной длины
    for (string& s : arr) {
        while (s.size() < max_length) {
            s.push_back('a');
        }
    }

    // Выполнение сортировки подсчетом для каждого разряда, начиная с самого правого
    for (int i = max_length - 1; i >= 0; i--) {
        counting_sort(arr, i);
    }

    // Удаление символов 'a', добавленных для выравнивания длин строк
    for (string& s : arr) {
        while (s.back() == 'a') {
            s.pop_back();
        }
    }
}

// Функция для генерации массива случайных строк заданной длины
vector<string> generate_random_strings(int n, int length)
{
    vector<string> result(n);
    for (int i = 0; i < n; i++) {
        string s(length, 'a');
        for (int j = 0; j < length; j++) {
            s[j] = 'a' + rand() % 26; // случайный символ от 'a' до 'z'
        }
        result[i] = s;
    }
    return result;
}

void print_strings(const vector<string>& arr)
{
    for (const string& s : arr) {
        cout << s << endl;
    }
}
