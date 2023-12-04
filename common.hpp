#pragma once

#include <vector>
#include <string>

std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> result;
    int pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}

template <typename Iterable>
class enumerate_object
{
private:
    Iterable _iter;
    std::size_t _size;
    decltype(std::begin(_iter)) _begin;
    const decltype(std::end(_iter)) _end;

public:
    enumerate_object(Iterable iter) : _iter(iter),
                                      _size(0),
                                      _begin(std::begin(iter)),
                                      _end(std::end(iter))
    {
    }

    const enumerate_object &begin() const { return *this; }
    const enumerate_object &end() const { return *this; }

    bool operator!=(const enumerate_object &) const
    {
        return _begin != _end;
    }

    void operator++()
    {
        ++_begin;
        ++_size;
    }

    auto operator*() const
        -> std::pair<std::size_t, decltype(*_begin)>
    {
        return {_size, *_begin};
    }
};

template <typename Iterable>
auto enumerate(Iterable &&iter)
    -> enumerate_object<Iterable>
{
    return {std::forward<Iterable>(iter)};
}

template <class T>
inline void hash_combine(std::size_t &seed, const T &v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
    template <typename T1, typename T2>
    struct hash<std::pair<T1, T2>>
    {
        size_t operator()(const std::pair<T1, T2> &p) const
        {
            std::size_t seed1(0);
            ::hash_combine(seed1, p.first);
            ::hash_combine(seed1, p.second);

            return seed1;
        }
    };
}
