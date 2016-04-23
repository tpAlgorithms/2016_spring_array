#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <exception>

struct my_hash_t {
  size_t operator()(const std::string &key) const {
    size_t out = 13;
    size_t A = 512764387;
    size_t M = 6128748162;
    for (size_t pos = 0; pos < key.size(); ++pos) {
      out = (out * A + key[pos]) % M;
    }
    return out;
  }
};

template <typename key_t, typename data_t, typename hash_func_t = my_hash_t>
struct hash_t {
  
  struct value_t {
    key_t key; // __DELETED , __EMPTY 
    data_t data; // -1 -> empty, -2 -> deleted
 
    enum state_t {
      EMPTY,
      DELETED,
      USED
    };
    
    state_t state;

    value_t() {
      state = EMPTY;
    }
  };
  typedef std::vector<value_t> value_vec_t;
  typedef typename value_vec_t::iterator iterator;

  value_vec_t data;
  size_t sz;
  hash_func_t hash_func;
  
  hash_t(size_t _capacity = 10):data(_capacity), sz(0) { }

  void grow() {
    printf("GROW: %d\n", 2 * data.size());
    hash_t<key_t, data_t, hash_func_t> tmp(2 * data.size());
    for (iterator it = begin(); it != end(); it = increment(it)) {
      tmp.add(it->key, it->data); 
    }
    std::swap(*this, tmp);
  }

  void add(const key_t &key, const data_t &value) {
    if (sz * 2 > data.size()) {
      grow(); 
    }
     
    size_t hash = hash_func(key);

    for (size_t prob = 0; prob < data.size(); ++prob) {
      size_t id = (hash + prob) % data.size();
      if (data[id].state != value_t::USED) {
        printf("ADD [%s] %d %d\n", key.c_str(), value, id);
        data[id].state = value_t::USED;
        data[id].key = key;
        data[id].data = value;
        ++sz;
        return;
      }
    }

    throw std::runtime_error("Not enough space");
  }

  size_t count(const key_t &key) const {
    size_t hash = hash_func(key);
    size_t cnt = 0;
    for (size_t prob = 0; prob < data.size(); ++prob) {
      size_t id = (hash + prob) % data.size();
      if (data[id].state == value_t::USED) {
        if (key == data[id].key) {
          ++cnt;
        }
      } else if (data[id].state == value_t::EMPTY) {
        return cnt; 
      }
    }
  }

  data_t& get(const key_t &key) { 
    size_t hash = hash_func(key);
    size_t cnt = 0;
    for (size_t prob = 0; prob < data.size(); ++prob) {
      size_t id = (hash + prob) % data.size();
      if (data[id].state == value_t::USED) {
        if (key == data[id].key) {
          return data[id].data;
        }
      }
    }

  }
  
  size_t size() {
    return sz;
  }

  bool is_empty(const typename value_vec_t::value_type &pair) {
    return pair.state != value_t::USED;
  }
  
  template <typename func_t>
  void foreach(func_t &func) {
    for (size_t pos = 0; pos < data.size(); ++pos) {
      if (! is_empty(data[pos])) {
        func(data[pos]);
      }
    }
  }

  iterator begin() {
    for (iterator it = data.begin(); it != data.end(); ++it) {
      if (! is_empty(*it)) {
        return it;
      }
    }
    return data.end();
  }

  iterator end() {
    return data.end();
  }

  iterator increment(iterator it) {
    ++it;
    for (; it != data.end(); ++it) {
      if (! is_empty(*it)) {
        return it;
      }
    }
    return data.end();
  }
  
};

void rstripln(char *str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}
static const size_t MAX_LEN = 64*1024;
int main() {

  typedef hash_t<std::string, int> map_t;
  map_t data;
  
  std::vector<char> buf(MAX_LEN);
  while(!feof(stdin)) {
    char *line = fgets(&buf[0], MAX_LEN, stdin);
    if (line == NULL || line[0] == '\0') break;
    rstripln(line);  
    //printf("[%s]\n", line);

    if (data.count(line) == 0) {
      //data[line] = 1;
      data.add(line, 1);
    } else {
      //data[line] += 1;
      data.get(line) += 1;
    }
  }

  for (map_t::iterator it = data.begin(); it != data.end(); it = data.increment(it)) {
    printf("%s => %d\n", it->key.c_str(), it->data);
  }

  return 0;
}
