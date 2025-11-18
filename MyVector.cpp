#include <iostream>
#include <string>
#include <list>
#include <stdexcept>    // out_of_range 예외를 위해 추가
using namespace std;

template<typename T>
class MyVector {
/* TODO */
private:
    T* data;         // 동적 배열을 가리키는 포인터
    size_t capacity; // 현재 할당된 배열 크기
    size_t length;   // 실제 저장된 요소 개수

    void resize() {
        cout << "Resize: " << capacity << " -> " << capacity * 2 << endl;
        
        size_t new_capacity = capacity * 2;
        T* new_data = new T[new_capacity];

        // 기존 데이터 복사
        for (size_t i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }

        // 기존 배열 해제
        delete[] data;

        // data 포인터와 capacity 업데이트
        data = new_data;
        capacity = new_capacity;
    }

public:
    // 생성자: 초기 capacity(2)로 배열 동적 할당
    MyVector() : capacity(2), length(0) {
        data = new T[capacity];
    }

    // 소멸자: 동적 메모리 해제
    ~MyVector() {
        delete[] data;
    }

    // push_back: capacity 초과 시 resize() 호출 후 값 추가
    void push_back(const T& value) {
        if (length == capacity) {
            resize();
        }
        data[length++] = value;
    }

    // pop_back: 마지막 항목을 리턴하고 제거
    T pop_back() {
        if (length == 0)
            throw out_of_range("Vector is empty");
        return data[--length];
    }

    // operator[]: 주어진 index의 요소를 반환
    // testVector의 for 루프가 size_t를 사용하므로 index 타입도 맞춤
    T& operator[](const size_t index){ 
        return data[index];
    }

    // const 객체에 대한 operator[] (좋은 습관)
    const T& operator[](const size_t index) const {
        return data[index];
    }

    // size: 현재 저장된 요소 개수를 반환
    size_t size() const {
        return length;
    }
};

template<typename T>
void testVector(const string& name, std::list<T> values) {

    cout << "------------------" << endl;
    MyVector<T> vec;
    for (auto& v : values)
        vec.push_back(v);

    cout << name << ": ";
    for (size_t i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";

    cout << endl;
    while(vec.size())
        cout << "Pop: " << vec.pop_back() << "\n";
}

int main() {
    testVector<int>("IntVec", {1, 2, 3, 4, 5, 6});
    testVector<double>("DoubleVec", {1.1, 2.2, 3.3, 4.4, 5.5});
    testVector<char>("CharVec", {'A', 'B', 'C', 'D', 'E', 'F'});
    testVector<string>("StringVec", {"Hello", "World", "C++", "Template", "Vector"});
    return 0;
}