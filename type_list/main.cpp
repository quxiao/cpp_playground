#include "type_list.h"

using namespace std;

int main()
{
    typedef TypeList<BlacklistFilter,
            TypeList<CateFilter,
            TypeList<StockFilter,
            NullType> > >
                FilterList;

    Goods example_goods;
    GoodsFilters<FilterList>::filter(example_goods);

    return 0;
}
