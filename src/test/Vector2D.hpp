//int,float,doubleのみ対応
//対応する型を増やしたい場合は以下に追記
template<class ...T>
struct Vector2D;

/*  以下特殊化  */
template<>
struct Vector2D<int>
{
    int x;
    int y;
};

template<>
struct Vector2D<float>
{
    float x;
    float y;
};

template<>
struct Vector2D<double>
{
    double x;
    double y;
};
