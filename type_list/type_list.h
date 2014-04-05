#ifndef TYPE_LIST_H
#define TYPE_LIST_H

#include <iostream>

/*
 * Type List
 */
template<typename H, typename T>
struct TypeList
{
    typedef H Head;
    typedef T Tail;
};

struct NullType {};

template<typename TypeList> struct Length {};

template<>
struct Length<NullType>
{
    enum {value = 0};
};

template<typename H, typename T>
struct Length< TypeList<H, T> >
{
    enum {value = 1 + Length<T>::value};
};

template<typename Tlist, typename T>
struct IndexOf {};

template<typename T>
struct IndexOf<NullType, T>
{
    enum {value = -1};
};

template<typename Tail, typename T>
struct IndexOf< TypeList<T, Tail>, T >
{
    enum {value = 0};
};

template<typename Head, typename Tail, typename T>
struct IndexOf< TypeList<Head, Tail>, T >
{
private:
    enum {temp = IndexOf<Tail, T>::value};
public:
    enum {value = temp == -1? -1: 1 + temp};
};


/*
 * TypeAt
 */

template<typename Tlist, int idx>
struct TypeAt;

template<typename H, typename S>
struct TypeAt<TypeList<H, S>, 0>
{
    typedef H Result;
};

template<typename H, typename S, int idx>
struct TypeAt<TypeList<H, S>, idx>
{
    typedef typename TypeAt<S, idx-1>::Result Result;
};


/*
 * Visitor
 */

template<typename Tlist>
struct TypeVisitor;

template<>
struct TypeVisitor<NullType>
{
    void static do_visit() {}
};

template<typename H, typename T>
struct TypeVisitor<TypeList<H, T> >
{
    void static do_visit()
    {
        std::cout << typeid(H).name() << std::endl;
        TypeVisitor<T>::do_visit();
    }
};

/*
 * Append
 */

template<typename Tlist, typename T>
struct Append;

template<>
struct Append<NullType, NullType>
{
    typedef NullType Result;
};

template<typename S>
struct Append<NullType, S>
{
    typedef TypeList<S, NullType> Result;
};

template<typename H, typename T, typename S>
struct Append<TypeList<H, T>, S>
{
    typedef TypeList<H, typename Append<T, S>::Result > Result;
};

template<typename H, typename T>
struct Append<NullType, TypeList<H, T> >
{
    typedef TypeList<H, T> Result;
};



/*
 * Reverse
 */

template<typename Tlist>
struct Reverse;


template<typename Tlist>
struct Reverse
{
    typedef typename Append<typename Reverse<typename Tlist::Tail>::Result, typename Tlist::Head>::Result
            Result;
};

template<>
struct Reverse<NullType>
{
    typedef NullType Result;
};

/*
 * Scatter Hierarchy
*/

template<class TypeList, template<class> class Unit>
class ScatterHierarchy;

template<class Head, class Tail, template<class> class Unit>
class ScatterHierarchy<TypeList<Head, Tail>, Unit>
    : public ScatterHierarchy<Head, Unit>
    , public ScatterHierarchy<Tail, Unit>
{
public:
    typedef ScatterHierarchy<Head, Unit> LeftBase;
    typedef ScatterHierarchy<Tail, Unit> RightBase;
};

template<class SingleType, template<class> class Unit>
class ScatterHierarchy: public Unit<SingleType>
{
public:
    typedef ScatterHierarchy<SingleType, Unit> LeftBase;
};

template<template<class> class Unit>
class ScatterHierarchy<NullType, Unit>
{};


template<class T>
struct Holder
{
    T _value;
};

template<class T, class TypeList, template <class> class Unit>
Unit<T>& Field(ScatterHierarchy<TypeList, Unit>& obj)
{
    return obj;
}


/*
 * Linear Hierarchy
 */

template<
    class Tlist,
    template<class SingleType, class Base> class Unit,
    class Root = NullType
>
class LinearHierarchy
{};

template<
    class Head,
    class Tail,
    template<class, class> class Unit,
    class Root
>
class LinearHierarchy<TypeList<Head, Tail>, Unit, Root>
    : public Unit< Head, LinearHierarchy<Tail, Unit, Root> >
{};

template<
    class T,
    template<class, class> class Unit,
    class Root
>
class LinearHierarchy<TypeList<T, NullType>, Unit, Root>
    : public Unit<T, Root>
{};



    struct Goods {};

    struct BlacklistFilter
    {
        bool static do_filter(Goods& goods) { std::cout << "BlacklistFilter" << std::endl; return true;}
    };

    struct CateFilter
    {
        bool static do_filter(Goods& goods) { std::cout << "CateFilter" << std::endl; return true;}
    };

    struct StockFilter
    {
        bool static do_filter(Goods& goods) { std::cout << "StockFilter" << std::endl; return true;}
    };

    template<typename Tlist>
    struct GoodsFilters
    {
        bool static filter(Goods& goods)
        {
            return Tlist::Head::do_filter(goods) 
                && GoodsFilters<typename Tlist::Tail>::filter(goods);
        }
    };

    template<>
    struct GoodsFilters<NullType>
    {
        bool static filter(Goods& goods) {return true;}
    };

#endif

