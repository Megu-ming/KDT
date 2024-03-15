#include <iostream>
#include <vector>
#include "Containers/Vector.h"
#include <format>

using std::cout;
using std::endl;

struct FStruct
{
    FStruct() = default;
    FStruct(const size_t InValue)
        :Value(InValue)
        , Pointer(new size_t(Value)) {}
    FStruct(const FStruct& InFStruct)
        :Value(InFStruct.Value)
        , Pointer(new size_t(Value)) {}
    // 이동생성자가 없으면 std::move를 해도 복사생성자가 호출
    FStruct(FStruct&& InFStruct) noexcept
        :Value(InFStruct.Value)
        , Pointer(InFStruct.Pointer) 
    {
        InFStruct.Value = 0;
        InFStruct.Pointer = nullptr;
    }
    ~FStruct() 
    {
        if (Pointer)
        {
            delete Pointer;
            Pointer = nullptr;
        }
    }

    size_t Value = 0;
    size_t* Pointer = new size_t(Value);
};

int main()
{
    int Value = KDT::Test();

    {
        cout << "KDT::vector" << endl;
        KDT::vector<int> Vector;
        for (int i = 0; i < 10; ++i)
        {
            cout << i << endl;
            Vector.push_back(i);
        }

        KDT::vector<FStruct> Vector2;
        //Vector2.reserve(10);
        for (int i = 0; i < 10; ++i)
        {
            Vector2.push_back(FStruct(i));
        }
        Vector2.resize(11);
        Vector2.resize(3);
        Vector2.clear();
        for (int i = 0; i < 5; ++i)
        {
            Vector2.push_back(FStruct(i));
        }

        size_t Size = Vector2.size();
        size_t Cap = Vector2.capacity();

        
        KDT::vector<FStruct>::iterator It = Vector2.begin();
        KDT::vector<FStruct>::iterator ItEnd = Vector2.end();
        ++It;
        --It;
        ++It;
        It++;
        ItEnd = It;
        
        for (FStruct& Value : Vector2)
        {
            cout << std::format("Value : {}\n", Value.Value);
        }

        FStruct& Data = Vector2[0];
        Data.Value = 89;
        FStruct& Data2 = Vector2[1];
        Data2.Value = 999;
    }
    {
        cout << "std::vector" << endl;
        std::vector<int> Vector;
        Vector.reserve(10);
        // 들어온 값만큼 새로운 메모리 공간 확보
        // 아무것도 없으면 그냥 확보
        // 뭔가 있었으면 메모리 공간 확보하고 원래값 옮기기
        cout << "for (int i = 0; i < 10; ++i) " << endl;
        for (int i = 0; i < 10; ++i)
        {
            cout << "i : " << i << endl;
            Vector.push_back(i);
        }
        cout << "for (int i : Vector)" << endl;
        for (int i : Vector)
        {
            cout << "i : " << i << endl;
        }

        std::vector<int>::iterator ItEnd = Vector.end();
        cout << "for (std::vector<int>::iterator It = Vector.begin(); It != ItEnd; ++It)" << endl;
        for (std::vector<int>::iterator It = Vector.begin(); It != ItEnd; ++It)
        {
            cout << "*It : " << *It << endl;
        }

        std::vector<int>::iterator It = Vector.begin();
        ++It;
        ++It;
        --It;
    }
    {
        std::vector<int> Vector;
        Vector.push_back(10);
        // 댕글링 포인터
        std::vector<int>::iterator It = Vector.begin();
        int& Value = Vector.back();
        // 재할당으로 인해 기존에 가리키던 주소가 무효화됨
        // Value, It가 의미없는 주소를 가리킴
        Vector.push_back(20);
    }
    {
        KDT::vector<int> Vector;
        Vector.push_back(10);
        // 댕글링 포인터
        KDT::vector<int>::iterator It = Vector.begin();
        int& Value = Vector[0];
        Vector.push_back(20);

        // 재할당으로 인해 기존에 가리키던 주소가 무효화됨
        // Value, It가 의미없는 주소를 가리킴
        Vector.push_back(20);
    }
}