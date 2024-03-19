#include "Pool.h"

class FClass
{
public:
    FClass()
    {
        cout << __FUNCTION__ << endl;
    }
    ~FClass()
    {
        cout << __FUNCTION__ << endl;
    }
};

int main()
{
    // new
    {
        FClass* Class = new FClass();
        /* 
            To Do...
        */
        delete Class;
    }
    // malloc
    {
        FClass* Class = (FClass*)malloc(sizeof(FClass));
        // placement new : 이미 할당된 메모리 블록에
        // 객체(인스턴스)를 만들어준다.(생성자 호출)
        new(Class)FClass();
        Class->~FClass();
        free(Class);
    }

    // Memory Pool : 큰 사이즈의 메모리 블록을 할당하고
    // 요청할 때 마다 미리 할당해둔 블록의 일부를 전달한다.
    // 요청이 만료되면 다시 풀에 환원된다.

    // 메모리 할당 : 커널에 요청하는 명령(system call)중 하나이다.
    // (OS가 최적화를 해놔서 매번 커널에 요청하는 것은 아닐 수도 있다)
    // 왜 커널에 요청하는가? 메모리는 공유 자산(내 프로그램만 쓰는 것이 아니다)
    // 이러한 공유자원을 사용하는 요청은(system call 중 하나) 동기화 처리가 되어야 할 것이다.
    // (여러 프로그램이 동시에 요청할 때 하나씩만 처리되어야 함)

    // 위와 같은 상황의 경우 최대한 커널 영역에 있는 시간을 줄여야 한다. (OS입장에서는)
    // 프로그램이 더 빠르게 동작한다고 할 수 있다.
    // 메모리 할당 및 해제를 빈번하게 하는 경우 메모리 풀을 만들어서 사용하면
    // 커널에 있는 시간을 많이 줄일 수 있다.

    // 메모리 풀을 사용했을 때 장점
    // - 속도가 빠르다(구현을 못하면 더 느리다; 어중간하면 new delete하는 것만 못하다)
    //      -> 결국 만들고 성능을 측정해야 한다.
    //      - 미리 적은 횟수의 시스템 콜로 메모리 블록을 할당하고 그것을 유저 영역에서 사용하기 때문에
    //      - [메모리 단편화 문제 해결] 큰 블록을 할당해두고 이를 유저가 쪼개서 사용하기 때문에 캐시 미스가 적다
    // 고정 사이즈 메모리 풀
    //      - 예산(메모리)를 정해서 그 예산 안에서 사용할게 제한할 수 있다.
    //          - ex)메모리풀 크기를 10으로 고정하면 최대 동시에 10개까지 (인스턴스)만들 수 있다.

    const size_t MaxCount = 100000;
    // array memory alloc time
    {
        auto Start{ chrono::steady_clock::now() };
        {
            for (size_t i = 0; i < MaxCount; ++i)
            {
                int* Test = new int[1024];
                delete[] Test;
            }
        }
        auto End{ chrono::steady_clock::now() };
        auto Diff{ End - Start };
        cout << format("new, delete :{}ms", chrono::duration<double, milli>(Diff).count());
    }
    cout << endl;
    // single var memory alloc time
    {
        auto Start{ chrono::steady_clock::now() };
        {
            for (size_t i = 0; i < MaxCount; ++i)
            {
                int* Test = new int;
                delete Test;
            }
        }
        auto End{ chrono::steady_clock::now() };
        auto Diff{ End - Start };
        cout << format("new, delete :{}ms", chrono::duration<double, milli>(Diff).count());
    }
    cout << endl;
    // selfmade memory pool time
    {
        //FMemoryPool MemoryPool{ sizeof(int)*1024,MaxCount };
        FMemoryPool MemoryPool{ 11,MaxCount }; // 얼라인이 안맞아서 성능 저하가 될 우려가 있다.
        auto Start{ chrono::steady_clock::now() };
        {

            for (size_t i = 0; i < 3; ++i)
            {
                int* Test = (int*)MemoryPool.malloc();
                
                MemoryPool.free(Test);
            }
        }
        auto End{ chrono::steady_clock::now() };
        auto Diff{ End - Start };
        cout << format("FMemoryPool :{}ms", chrono::duration<double, milli>(Diff).count());
    }
    cout << endl;
    // boost memory pool time
    {
        boost::pool<> Pool{ sizeof(int) * 1024,MaxCount };
        int* TryAlloc = (int*)Pool.malloc();
        Pool.free(TryAlloc);

        auto Start{ chrono::steady_clock::now() };
        {
            for (size_t i = 0; i < MaxCount; ++i)
            {
                int* Test = (int*)Pool.malloc();
                Pool.free(Test);
            }
        }
        auto End{ chrono::steady_clock::now() };
        auto Diff{ End - Start };
        cout << format("Boost Pool :{}ms\n", chrono::duration<double, milli>(Diff).count());
    }
    // Object Pool : 메모리풀은 순수한 메모리 블락만 가지고 있고,
    // 오브젝트 풀은 placement new를 사용해서 Object를 만들어주는 기능이 추가됨
    {
        struct FData
        {
            FData()
            {
                //cout << __FUNCTION__ << endl;
            }
            FData(const int InA, const int InB)
            {

            }
            ~FData()
            {
                //cout << __FUNCTION__ << endl;
            }
        };
        // boost::object_pool
        {
            boost::object_pool<FData> ObjectPool{ MaxCount };
            ObjectPool.free(ObjectPool.malloc());

            auto Start{ chrono::steady_clock::now() };
            {
                for (size_t i = 0; i < MaxCount; ++i)
                {
                    FData* Data = ObjectPool.construct();
                    ObjectPool.destroy(Data);
                }
            }
            auto End{ chrono::steady_clock::now() };
            auto Diff{ End - Start };
            cout << format("Object Pool :{}ms\n", chrono::duration<double, milli>(Diff).count());
        }
        // boost::object_pool_smart pointer
        {
            boost::object_pool<FData> ObjectPool{ MaxCount };
            ObjectPool.free(ObjectPool.malloc());

            auto Start{ chrono::steady_clock::now() };
            {
                for (size_t i = 0; i < MaxCount; ++i)
                {
                    FData* Data = ObjectPool.construct();
                    shared_ptr<FData>{Data, [&ObjectPool](FData* InPointer) {ObjectPool.destroy(InPointer); }};
                    /*ObjectPool.destroy(Data);*/
                }
            }
            auto End{ chrono::steady_clock::now() };
            auto Diff{ End - Start };
            cout << format("Object Pool_shared :{}ms\n", chrono::duration<double, milli>(Diff).count());
        }
        // selfmade object_pool
        {
            FObjectPool<FData> ObjectPool{ MaxCount };

            auto Start{ chrono::steady_clock::now() };
            {
                for (size_t i = 0; i < MaxCount; ++i)
                {
                    FData* Data = ObjectPool.construct((int)i, 10);
                    ObjectPool.destroy(Data);
                }
            }
            auto End{ chrono::steady_clock::now() };
            auto Diff{ End - Start };
            cout << format("FObjectPool :{}ms\n", chrono::duration<double, milli>(Diff).count());
        }
        // selfmade object_pool shared_ptr
        {
            FObjectPool<FData> ObjectPool{ MaxCount };
            shared_ptr<FData> Test;
            auto Start{ chrono::steady_clock::now() };
            {
                for (size_t i = 0; i < MaxCount; ++i)
                {
                    shared_ptr<FData> Data = ObjectPool.construct_shared((int)i, 10);
                    if (i == 0)
                        Test = Data;
                }
            }
            auto End{ chrono::steady_clock::now() };
            auto Diff{ End - Start };
            cout << format("FObjectPool_shared :{}ms\n", chrono::duration<double, milli>(Diff).count());
        }
    }
}