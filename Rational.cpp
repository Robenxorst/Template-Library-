#include <iostream>

//класс рациональных дробей

struct Rational
{
    explicit Rational(int numerator = 0, int denominator = 1) :
    numerator_(numerator), denominator_(denominator) {};

    Rational(Rational const &that) {
        numerator_ = that.numerator_;
        denominator_ = that.denominator_;
    }//если нам на вход поступит рациональный класс, а не два числа

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);
    //оператор приведения значения класса к double
    operator double() const
    {
        return this->to_double();
    }

    Rational operator+() const{
        return Rational(numerator_, denominator_);
    }

    Rational operator-() const{
        return Rational(-numerator_, denominator_);
    }

    Rational &operator+=(Rational const & that) {
        this->add(that);
        return *this;
    }

    Rational &operator-=(Rational const & that) {
        this->sub(that);
        return *this;
    }

    Rational &operator*=(Rational const &that) {
        this->mul(that);
        return *this;
    }

    Rational &operator/=(Rational const &that) {
        this->div(that);
        return *this;
    }

    void neg();
    void inv();
    double to_double() const;
    int get_num() const { return numerator_; }
    int get_dev() const { return denominator_; }

private:
    int numerator_;//числитель
    int denominator_;//знаменатель
};

void Rational::add(Rational rational) {
    numerator_ = numerator_ * rational.denominator_ + denominator_ * rational.numerator_;
    denominator_ *= rational.denominator_;
}

void Rational::sub(Rational rational) {
    numerator_ = numerator_ * rational.denominator_ - denominator_ * rational.numerator_;
    denominator_ *= rational.denominator_;
}

void Rational::mul(Rational rational) {
    numerator_ *= rational.numerator_;
    denominator_ *= rational.denominator_;
}

void Rational::div(Rational rational) {
    numerator_ *= rational.denominator_;
    denominator_ *= rational.numerator_;
}

void Rational::neg(){
    numerator_ = -numerator_;
}

double Rational::to_double() const{
    return numerator_ / (double) denominator_;
}

//Rational &operator+=(int number, Rational &rational) {
//    return rational += Rational(number, 1);
//}
//
//Rational &operator-=(int number, Rational &rational) {
//    return rational -= Rational(number, 1);
//}
//
//Rational &operator*=(int number, Rational &rational) {
//    return rational *= Rational(number, 1);
//}
//
//Rational &operator/=(int number, Rational &rational) {
//    return rational /= Rational(number, 1);
//}

Rational operator+(Rational r1, Rational const & r2)
{
    return r1 += r2;
}

Rational operator-(Rational r1, Rational const & r2)
{
    return r1 -= r2;
}

Rational operator*(Rational r1, Rational const & r2)
{
    return r1 *= r2;
}
Rational operator/(Rational r1, Rational const & r2)
{
    return r1 /= r2;
}

bool operator<(Rational const & r1, Rational const & r2)
{
    return (r1.get_num() * r2.get_dev()) < (r2.get_num() * r1.get_dev());
}

bool operator>(Rational const & r1, Rational const & r2)
{
    return r2 < r1;
}

bool operator<=(Rational const & r1, Rational const & r2)
{
    return  !(r2<r1);
}

bool operator>=(Rational const & r1, Rational const & r2)
{
    return !(r1<r2);
}

bool operator==(Rational const & r1, Rational const & r2)
{
    return !(r1<r2) && !(r2<r1);
}

bool operator!=(Rational const & r1, Rational const & r2)
{
    return (r1<r2) || (r2<r1);
}

int main() {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3(5);

    r1.add(r2);
    std::cout << r1.to_double() << std::endl;
    r1.sub(r2);
    std::cout << r1.to_double() << std::endl;
    r1.neg();
    std::cout << r1.to_double() << std::endl;
    r3.mul(r1);
    std::cout << r3.to_double() << std::endl;
    r3.div(r2);
    std::cout << r3.to_double() << std::endl;

//    Rational r1(1,2);
//    Rational r2(1,3);
//    double D = r1;
//    std::cout << D << std::endl;
//    bool rez;
//    rez = (r2 < r1);
//    std::cout << rez << std::endl;
//    int i = 1;
//    Rational r2 = (i -= r1);
//    std::cout << r2.to_double() << std::endl;
//    Rational r3 = (r1 + r2);
//    std::cout << r3.to_double() << std::endl;

}
