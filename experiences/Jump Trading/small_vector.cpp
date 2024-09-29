/*
std::vector has infinite capacity and always allocates. However, sometimes we find ourselves in a situation where 90% of the time we'll have at most... 5 elements. We might still get 50 or 500 or 5 million, but typically we'll have 5. We'd like to avoid having to do an allocation for the first few elements to save the time.

Implement small_vector<T, N>, a contiguous container where the first N elements will be stored in automatic storage within the container, but will fallback to putting them on the heap.
*/

#include <array>
// #include <type_traits>
#include <vector>
#include <algorithm>

template <typename T, size_t N>
struct small_vector {
    std::array<T, N> small_store;
    std::vector<T> heap_store;

    // std::aligned_storage<sizeof(T), alignof(T)> small_store[N];
    // new (&small_store[sz++]) T;
  
    size_t sz{0};

    void push_back(T const& t){
      if (sz < N && heap_store.capacity() == 0)
      {
        small_store[sz++] = t;
      }
      else if (heap_store.capacity() == 0)
      {
        heap_store.resize(N+1);
        std::copy(small_store.cbegin(), small_store.cend(), heap_store.begin());
        heap_store.push_back(t);
      }
      else
      {
        heap_store.push_back(t);
      }
    };

    T pop_back() {
      if (heap_store.capacity() == 0) {
        T r = small_store[--sz];
        small_store[sz+1].~T();
        return r;
      }
      return heap_store.pop_back();
    };

    T& front() {
      if (heap_store.capacity() == 0) {
        return small_store.front();
      }
      return heap_store.front();
    };
};

// 5, ->10, <-10, ->1
