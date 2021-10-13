#include <iostream>

typedef int Image;

template<class T>
struct Vector2D
{
    T x;
    T y;
};

//char型のvector2Dは定義しない
template<>
struct Vector2D<char>;

typedef Vector2D<int> Size2D;
typedef Vector2D<float> Position;
struct ObjInfo
{
    Position position;
    Size2D size;
};

struct ButtonInfo
{
    ObjInfo info;
    unsigned int color;
    bool fill;
};


class Object{
private:
    Image img = 1;
public:
    virtual void Update() = 0;
};

class GUI : public Object
{
public:
    virtual void Event() = 0;
};

template <class ...T>
class Button;

template <class T>
class Button<T> : public GUI
{
private:
    void OnClick(){/* 登録された関数を実行 */};
    //イベント実行
    void Event(){
        OnClick();
    }
public:
    Button(){};
    Button(ButtonInfo info){}
    ~Button(){};
    void Update(){
        if(/*クリック判定*/){
            OnClick();
        }
    };
};

int main()
{
    Object* array[3];
    array[0] = new Button<int>();
    array[1] = new Button<void>();
    array[2] = new Button<char>();

    GUI* obj[3];
    obj[0] = new Button<int>();
    obj[1] = new Button<void>();
    obj[2] = new Button<char>();
    
    for(auto i : array){
        i->Update();
    }

    for(auto i : obj){
        i->Update();
    }

    return 0;
}