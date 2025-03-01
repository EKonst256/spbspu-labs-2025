#include "list_actions.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <list>
#include <stdexcept>
#include <string>

namespace
{
  bool summ_overflow(size_t a, size_t b)
  {
    size_t n = std::numeric_limits< size_t >::max();
    if (n - a < b)
    {
      return 1;
    }
    return 0;
  }
}

std::list< pair_t > *evstyunichev::form_list(std::istream &in)
{
  std::list< pair_t > *sequences = new std::list< pair_t >;
  std::string str = "";
  while (in >> str)
  {
    if (isalpha(str[0]))
    {
      sequences->push_back({str, {} });
    }
    else
    {
      size_t n = std::stoull(str);
      sequences->back().second.push_back(n);
    }
  }
  return sequences;
}

std::ostream &evstyunichev::list_out(std::list< pair_t > *sequences, std::ostream &out)
{
  bool overflow_flag = false;
  if (sequences->empty())
  {
    out << "0";
    return out;
  }
  std::list< size_t > summ{};
  auto iter_seq = sequences->begin();
  size_t mx = iter_seq->second.size();
  out << (iter_seq++)->first;
  for (; iter_seq != sequences->end(); ++iter_seq)
  {
    out << ' ' << iter_seq->first;
    mx = std::max(mx, iter_seq->second.size());
  }
  if (!mx && !overflow_flag)
  {
    out << '\n';
    summ.push_back(0);
  }
  for (size_t i = 0; i < mx; i++)
  {
    auto iter_seq = sequences->begin();
    out << '\n';
    for (iter_seq = sequences->begin(); iter_seq->second.empty(); ++iter_seq);
    size_t num = iter_seq->second.front();
    iter_seq->second.pop_front();
    out << num;
    if (!overflow_flag)
    {
      summ.push_back(num);
    }
    ++iter_seq;
    for (; iter_seq != sequences->end(); ++iter_seq)
    {
      if (iter_seq->second.empty())
      {
        continue;
      }
      size_t num = iter_seq->second.front();
      out << ' ' << num;
      if (!overflow_flag)
      {
        if (!summ_overflow(summ.back(), num))
        {
          summ.back() += num;
        }
        else
        {
          overflow_flag = 1;
        }
      }
      iter_seq->second.pop_front();
    }
  }
  if (!overflow_flag)
  {
    if (mx)
    {
      out << '\n';
    }
    auto it = summ.begin();
    out << *(it++);
    for (; it != summ.end(); it++)
    {
      out << ' ' << *it;
    }
  }
  else
  {
    out << "\n";
    throw std::overflow_error("overflow!");
  }
  return out;
}
