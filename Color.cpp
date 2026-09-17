#include "Color.hpp"
#include <fstream>

Color::Color() = default;

Color::Color(double red, double green, double blue)
    : r{red}, g{green}, b{blue} {}

double Color::red() const {
    return r;
}

double Color::green() const {
    return g;
}

double Color::blue() const {
    return b;
}

void Color::setRGB(const double red, const double green, const double blue) {
    this->r = red;
    this->g = green;
    this->b = blue;
}

/**
 * Operator to read Color from input stream.
 *
 * @param is input stream.
 * @param c Color object to write in
 * @return input stream.
 */
std::istream& operator>>(std::istream& is, Color& c) {
    /*
     * ИМПЛЕМЕНТАЦИЯ ПЕРЕГРУЗКИ ОПЕРАТОРА >>:
     * Было решено создать новый метод setRGB() в классе Color,
     * который изменяет значения полей r, g, b.
     * Сами же поля r, g, b остаются закрытыми для изменения извне.
     * Это позволит нам контролировать в будующем, где и как поменялся цвет.
     * Инкапсуляция!
     *
     * Также можно было просто сделать поля r, g, b открытыми
     * и изменять их непосредственно в коде вне класса.
     * Но такое решение в лоб позволит кому угодно, где угодно и как угодно
     * изменять значение цвета, что сницит контроль.
     */
    double red, green, blue;
    is >> red >> green >> blue;

    c.setRGB(red, green, blue);

    return is;
}
