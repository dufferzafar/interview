#include <unordered_map>
#include <list>

template <typename KeyT, typename ValT>
class LRUCache {

  private:
  int capacity{0};
  std::list< std::pair<KeyT, ValT> > items;
  std::unordered_map<KeyT, typename std::list< std::pair<KeyT, ValT> >::iterator > map;

  std::mutex mtx;

  public:

  LRUCache(int max_capacity) : capacity{max_capacity} {}

  void set(const KeyT& key, const ValT& val)
  {
    auto it = map.find(key);
    // key exists, update!
    if (it != map.end())
    {
      it->second->second = val;
      items.splice(items.begin(), items, it->second);
      return;
    }

    // if full capacity -> evict!
    if (items.size() == capacity)
    {
      // Get tail of the list
      auto end = items.back();
      map.erase(end.first);
      items.pop_back();
    }

    // add to both map & list?
    items.emplace_front(key, val);
    map[key] = items.begin();
  };

  bool get(const KeyT& key, ValT& val) {
    auto it = map.find(key);
    // key doesn't exist, error!
    if (it == map.end())
    {
      return false;
    }

    // Update my list to put key at the front?
    items.splice(items.begin(), items, it->second);

    // Return Val for key
    val = it->second->second;
    return true;
  };

};

int main()
{

  

  return 0;
}
