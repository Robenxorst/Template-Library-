#ifndef BINARY_OPERATION_VIRTUAL_METHODS
#define BINARY_OPERATION_VIRTUAL_METHODS

#include <string>

struct Expression
{
    virtual double evaluate() const = 0;
    virtual ~Expression() {}
};

struct Number : Expression
{
    explicit Number(double value)
            : value(value)
    {}
    double evaluate() const override {return value; }

private:
    double value;
};

struct BinaryOperation : Expression
{
    /*
      Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих операциям,
      которые реализуются.
     */
    BinaryOperation(Expression const * left_, char op_, Expression const * right_)
    {
        this->left = left_;
        this->op = op_;
        this->right = right_;
    }

    ~BinaryOperation()
    {
        delete left;
        delete right;
    }

    double evaluate() const override {
        if(op == '+')
            return((*left).evaluate() + (*right).evaluate());
        else if(op == '-')
            return((*left).evaluate() - (*right).evaluate());
        else if(op == '*')
            return((*left).evaluate() * (*right).evaluate());
        else if(op == '/')
            return((*left).evaluate() / (*right).evaluate());
        else
            return 0;
    }

private:
    Expression const * left;
    Expression const * right;
    char op;
};

#endif

//// Пример применения структур

//int main()
//{
//// записываем код 3 + 4.5 * 5 с итогом 25.5
//    Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
//// потом используем его в выражении для +
//    Expression * expr = new BinaryOperation(new Number(3), '+', sube);
//
//// вычисляем и выводим результат: 25.5
//    std::cout << expr->evaluate() << std::endl;
//
//// тут освобождаются *все* выделенные объекты
//// (например, sube будет правым операндом expr, поэтому его удалять не нужно)
//    delete expr;
//    return 0;
//}