#include <iostream>
#include <string>

//https://refactoring.guru/ru/design-patterns/visitor/cpp/example - концептуальный пример

struct Number;          //  изначально объявляем структуры классов
struct BinaryOperation;//   которые используются в методах Visitor

struct Visitor// сам базовый абстрактный класс Посетителя, где объявлены пустые методы
{
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * binary) = 0;
    virtual ~Visitor() { }
};

struct Expression// базовый абстрактный класс Выражение
{
    virtual double evaluate() const = 0;
    virtual void visit(Visitor * visitor) const = 0;
    //абстрактный метод, принимающий на вход объект, реализующий методы Посетителя;
    virtual ~Expression() { }
};

struct Number : Expression//класс Номер, содержащий значение value
{
    explicit Number(double value) : value(value) {} //конструктор
    void visit(Visitor *visitor) const override
    { visitor->visitNumber(this); }//полиморфный метод,вызывающий конкртный метод Посетителя для своего класса
    double get_value() const { return value;}// слово const значит,что мы никак не изменяем поля класса
    double evaluate() const { return value; }

private:
    double value;
};

struct BinaryOperation : Expression//класс БинарнойОперации, определяющий результат операции
{
    BinaryOperation(Expression const * left_, char op_, Expression const * right_)
    {
        this->left = left_;
        this->op = op_;
        this->right = right_;
    } // конструктор класса

    void visit(Visitor * visitor) const override//аналогичный полиморфный метод
    { visitor->visitBinaryOperation(this); }
    Expression const * get_left()  const { return left; }//доступ к левому
    Expression const * get_right() const { return right; }//и правому операндам
    char get_op() const { return op; }//доступ к знаку операции


    double evaluate() const
    {
        if (op == '+')
            return (left->evaluate() + right->evaluate());
        else if (op == '-')
            return (left->evaluate() - right->evaluate());
        else if (op == '*')
            return (left->evaluate() * right->evaluate());
        else if (op == '/')
            return (left->evaluate() / right->evaluate());
        return 0;
    }

    ~BinaryOperation()
    {
        delete left;
        delete right;
    }// деструктор класса


private:
    Expression const * left;
    Expression const * right;
    char op;
};

//далее идут наследники Посетителя(КонкретныеПосетители),
//котроые могут реализовывать методы конкретных компонентов(Номер, БинарнаяОперация)

struct PrintVisitor : Visitor
{
    void visitNumber(Number const * number)
    {
        double x = number->evaluate();
        if (x < 0)
            std :: cout << "(" << x << ")";//если меньше нуля, то число в скобках;
        else
            std :: cout << x;
    }

    void visitBinaryOperation(BinaryOperation const * bop)
    {
        bool is_prev = this->is;
        char c = bop->get_op();
        bool is_cur = is_prev && (c == '-' || c == '+'); // если встретили
        // неприоритетную операцию, то используем скобку
        if(is_cur)
            std::cout<< "(";
        this->is = (c == '*' || c == '/'); // появилась приоритетная операция
        bop->get_left()->visit(this);

        std::cout << c;

        this->is = (c=='*'|| c =='/'); //сообщаем внутрь, что у нас приоритетная операция
        bop->get_right()->visit(this);

        if(is_cur)
            std::cout << ")";
        this->is = is_prev;      //вернем в начальное состояние
    }
private:
    bool is = false;
};

// Описание команды bop->get_left()->visit(this) :
// visit -- виртуальный метод класса Expression.
// Когда Вы вызываете, допустим, bop->get_left()->visit(this),
// программа смотрит на таблицу виртуальных функций
// объекта bop->get_left() и находит там функцию visit,
// соответствующую его классу. Если bop->get_left()
// на самом деле Number, то будет вызван его visit,
// который вызовет visitor->visitNumber(this),
// а если bop->get_left() на самом деле BinaryOperation,
// то будет вызван visit этого класса.

int main()
{
    Expression * sube = new BinaryOperation(new Number(4.5), '+', new Number(5));
    Expression const * expr = new BinaryOperation(new Number(3), '*', sube);
    PrintVisitor visitor;
    expr->visit(&visitor);
}