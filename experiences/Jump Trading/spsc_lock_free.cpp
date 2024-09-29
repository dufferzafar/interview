#include <iostream>
#include <atomic>
#include <array>

using namespace std;


template <typename T, size_t N>
// Add concept requirement over T to be default constructible etc.
class SPSCFixedQueue {

  private:

  std::array<T, N> buffer;
  // std::vector<T, N> buffer;
  atomic<size_t> head;
  atomic<size_t> tail;

  // optimization
  // N == 2**n, % => (& N-1)

  public:

  SPSCFixedQueue() : head{0}, tail{N-1} {}

  // bool try_push(T&& item) { }

  bool try_push(const T& item) {
    auto current = head.load();
    auto next = (current + 1) % N;
    if (current == tail.load())
    {
      return false;
    }
    buffer[current] = move(item);
    head.store(next);
    return true;
  };

  bool try_pop(T& item) {
    auto current = tail.load();
    if (current == head)
    {
      return false;
    }
    item = buffer[current];
    // call buffer[current].~T(); ??
    auto next = (tail + 1) % N;
    tail.store(next);
    return true;
  };

};

// To execute C++, please define "int main()"
int main() {
  SPSCFixedQueue<int, 5> Q;
  int j = 10;
  Q.try_push(j);

  Q.try_push(18);
  Q.try_push(19);
  Q.try_push(20);
  Q.try_push(21);

  int e;
  Q.try_pop(e);
  cout << e;
  cout << endl;

  Q.try_pop(e);
  cout << e;
  cout << endl;

  Q.try_pop(e);
  cout << e;
  cout << endl;

  Q.try_pop(e);
  cout << e;
  cout << endl;

  Q.try_pop(e);
  cout << e;
  cout << endl;

  return 0;
}
