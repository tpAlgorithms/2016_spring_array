#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

typedef int data_t;
/*
a < b;
less(a, b); cmp(a,b) < 0;

a >= b; !(a < b);
!less(a, b); cmp(a,b) >= 0;

a <= b;
!less(b, a);

a > b
less(b, a);

!(less(a,b) || less(b,a))
*/

bool eu_less(const data_t& lhs, const data_t& rhs) {
  return lhs < rhs;
}

void date_parse_us(int date, int &year, int &month, int &day) { 
  year = date / 10000; 
  month = date % 100;
  day = (date / 100) % 100;
}

bool us_less(const data_t& lhs, const data_t& rhs) {
  //YYYYDDMM
  int lhs_year;
  int lhs_month;
  int lhs_day;

  int rhs_year;
  int rhs_month;
  int rhs_day;

  date_parse_us(lhs, lhs_year, lhs_month, lhs_day);
  date_parse_us(rhs, rhs_year, rhs_month, rhs_day);

  if (lhs_year != rhs_year) {
    return lhs_year < rhs_year;
  }
  if (lhs_month != rhs_month) {
    return lhs_month < rhs_month;
  }
  return lhs_day < rhs_day;
}

template <typename less_t>
void merge(data_t *a, int sz_a, data_t *b, int sz_b, data_t *tmp, less_t& less) {
  int i = 0;
  int j = 0;
  for (; i < sz_a && j < sz_b;) {
    if (!less(b[j], a[i])) {
      tmp[i+j] = a[i];
      ++i;
    } else {
      tmp[i+j] = b[j];
      ++j;
    }
  }
  for (; i < sz_a; ++i) {
    tmp[i+j] = a[i];
  }
  for (; j< sz_b; ++j) {
    tmp[i+j] = b[j];
  }
}

template <typename less_t>
void my_sort(data_t *data, int size, less_t &less) { 
  //std::sort(&data[0], &data[size], less);
  if (size <= 1) return;
  data_t *tmp = new data_t[size];

  my_sort(data, size/2, less);
  my_sort(&data[size/2], size - size/2, less);

  merge(data, size/2, &data[size/2], size - size/2, tmp, less);

  for(int i = 0; i < size; ++i) {
    data[i] = tmp[i];
  }
  delete [] tmp;
}


int main() {
  std::vector<int> data;

  int value;
  while(scanf("%d", &value) == 1) {
    data.push_back(value);
  }

  my_sort(&data[0], data.size(), us_less);

  for (int c = 0; c < data.size(); ++c) {
    printf("%d\n", data[c]);
  }

  return 0;
}
