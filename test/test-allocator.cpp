#include "catch.hpp"
#include "BasicString.hpp"

template<class T>
struct bad_allocator : std::allocator<T>
{
    typedef size_t            size_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;

    pointer allocate(size_type __n, bad_allocator<T>::const_pointer = 0) {
        throw std::bad_alloc();
    }
};

TEST_CASE("bad_alloc")
{
    SECTION("bad_alloc")
    {
        using bad_string = BasicString<char, std::char_traits<char>, bad_allocator<char> >;
        // creating an object should throw
        CHECK_THROWS_AS(bad_string(), std::bad_alloc);
    }
}

template <class T>
struct my_allocator {
    using value_type = T;
    my_allocator() {}

    template <class U>
    my_allocator(const my_allocator<U>&) {}

    T* allocate(std::size_t n)
    {
    	printf("my_allocator::allocate()\n");

        return reinterpret_cast<T*>(std::malloc(sizeof(T) * n));
    }

    void deallocate(T* p, std::size_t n)
    {
    	printf("my_allocator::deallocate()\n");
        static_cast<void>(n);
        std::free(p);
    }
};

template <class T, class U>
bool operator==(const my_allocator<T>&, const my_allocator<U>&)
{ return true; }

template <class T, class U>
bool operator!=(const my_allocator<T>&, const my_allocator<U>&)
{ return false; }



TEST_CASE("custom_alloc")
{
    SECTION("custom_alloc")
    {
        using custom_string = BasicString<char, std::char_traits<char>, my_allocator<char> >;

        CHECK_NOTHROW(custom_string("testeeeeeeeeeeeeeeeee"));
    }
}