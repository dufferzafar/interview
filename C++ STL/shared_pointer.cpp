#include <iostream>

#include <memory>

namespace my {
template <typename T> class shared_ptr {
  T *ptr;

  // Where should the reference count be stored?
  // ~~Should it be static?~~
  // Should it on the [heap]? or on stack?
  int *refcnt;

public:
  shared_ptr() : ptr{nullptr}, refcnt{nullptr} {}
  shared_ptr(T *p) : ptr{p}, refcnt{new int(1)} {}

  ~shared_ptr() {
    if (ptr) {
      if (--(*refcnt) == 0) {
        delete ptr;
        delete refcnt;
      }
    }
  }

  [[nodiscard]] T *get() { return ptr; }

  T *operator->() { return ptr; }
  T &operator*() { return *ptr; }

  operator bool() const { return ptr != nullptr; }

  void reset(T *p = nullptr) {
    if (ptr) {
      if (--(*refcnt) == 0) {
        delete ptr;
        delete refcnt;
      }
    }
    ptr = p;
    if (ptr) {
      refcnt = new int(1);
    } else {
      refcnt = nullptr;
    }
  }

  shared_ptr(const shared_ptr<T> &rhs) : ptr{rhs.ptr}, refcnt{rhs.refcnt} {
    if (ptr) {
      ++(*refcnt);
    }
  }
  shared_ptr &operator=(const shared_ptr<T> &rhs) {
    if (this != &rhs) {
      reset();
      ptr = rhs.ptr;
      refcnt = rhs.refcnt;
      if (ptr) {
        ++(*refcnt);
      }
    }
    return *this;
  }

  shared_ptr(shared_ptr<T> &&rhs) : ptr{rhs.ptr}, refcnt{rhs.refcnt} {
    rhs.ptr = nullptr;
    rhs.refcnt = nullptr;
  }
  shared_ptr &operator=(shared_ptr<T> &&rhs) {
    if (this != &rhs) {
      reset();
      ptr = rhs.ptr;
      refcnt = rhs.refcnt;
      rhs.ptr = nullptr;
      rhs.refcnt = nullptr;
    }
    return *this;
  }
};
} // namespace my

void ours() {
  using namespace my;
  shared_ptr<int> s1(new int(9));
  shared_ptr<int> s2(s1);
  s1.reset();

  s2 = s1;
  s2 = std::move(s1);

  std::cout << *(s1.get());
}

void theirs() {
  using namespace std;

  {
    shared_ptr<int> p(new int(9));
    p = p;
  }

  shared_ptr<int> q(new int(9));
  shared_ptr<int> r(q);
  r.reset();

  shared_ptr<int> s = std::move(q);
}

int main() { return 0; }

