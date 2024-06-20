#include <iostream>
#include <cmath>

class Complex {
private:
    double real; //variable privée qui def un nb cplx
    double imaginary;

public:
   
    Complex() : real(0), imaginary(0) {} //constructeurs
    Complex(double r, double i) : real(r), imaginary(i) {}


    //remplacer op + - * /  par la vraie fonction car c'est une classe on peut pas juste fait class * class
    //plus beau d'ecraser les operateurs par nouvelle fonction que d'avoir une nouvelle methode a chaque fois

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) { //utilise friend pour acceder aux membres privée permet de cout <<
        if (c.imaginary >= 0)
            os << c.real << " + " << c.imaginary << "i";
        else
            os << c.real << " - " << -c.imaginary << "i";
        return os;
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    Complex operator*(const Complex& other) const {
        double r = real * other.real - imaginary * other.imaginary;
        double i = real * other.imaginary + imaginary * other.real;
        return Complex(r, i);
    }
    Complex operator/(const Complex& other) const { 
        double denominator = other.real * other.real + other.imaginary * other.imaginary;
        double r = (real * other.real + imaginary * other.imaginary) / denominator;
        double i = (imaginary * other.real - real * other.imaginary) / denominator;
        return Complex(r, i);
    }
    bool operator==(const Complex& other) const { //crée la comparaison pour nb complexe peut peut etre simplifier par comparer bits
        return real == other.real && imaginary == other.imaginary;
    }

    Complex conjugate() const { //simplement - imaginary pour avoir le conjuger
        return Complex(real, -imaginary);
    }
    void toExponential() const { //conversion en forme exponentielle
        double r = module();
        double theta = argument();
        std::cout << r << " * e^(" << theta << "i)" << std::endl;
    }

   
    Complex& operator++() {  //remplacer l'operateur ++ et -- en 2 etapes avec pass de self
        ++real;
        return *this;
    }
    Complex operator++(int) { //le int sert juste a dif a remplacer par better
        Complex temp = *this; //this equivalent de self en python
        ++real;
        return temp;
    }
    Complex& operator--() { //same
        --real;
        return *this;
    }
    Complex operator--(int) { //same
        Complex temp = *this;
        --real;
        return temp;
    }

    bool operator<(const Complex& other) const { //transformer l'operateur comparaison pour comparer le module des nombres complex passer en arg
        return this->module() < other.module();
    }
    bool operator>(const Complex& other) const { //same
        return this->module() > other.module();
    }
    double module() const { //retourne le module du nb cplx
        return std::sqrt(real * real + imaginary * imaginary);
    }
    double argument() const { //retourne l'arg du nb cplx
        return std::atan2(imaginary, real);
    }
    double getReal() const { //juste fonction return le reel du nb cplx
        return real;
    }
    double getImaginary() const { //juste fonction return l'imaginaire du nb cplx
        return imaginary;
    }
};

int main() {
    Complex c1(5, 69);
    Complex c2(15, 2);
    
    std::cout << "imaginaire : " << c1.getImaginary() << std::endl;
    std::cout << "reel : " << c1.getReal() << std::endl;

    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;

    Complex sum = c1 + c2;
    std::cout << "somme : " << sum << std::endl;

    Complex diff = c1 - c2;
    std::cout << "difference : " << diff << std::endl;

    Complex product = c1 * c2;
    std::cout << "produit : " << product << std::endl;

    Complex quotient = c1 / c2;
    std::cout << "quotien : " << quotient << std::endl;

    std::cout << "module de c1 : " << c1.module() << std::endl;
    std::cout << "argument de c1 : " << c1.argument() << std::endl;

    Complex conj = c1.conjugate();
    std::cout << "Conjugate of c1 : " << conj << std::endl;

    std::cout << "c1 forme exp : ";
    c1.toExponential(); //pourais implementer une classe exponantial et clas ... ... ... et faire que la fonction return le type classe exponantial mais pas le temp

    std::cout << "incremente c1 : " << ++c1 << std::endl;
    std::cout << "decremente c1 : " << --c1 << std::endl;

    if (c1 == c2) {
        std::cout << "c1 = c2" << std::endl;
    }
    else {
        std::cout << "c1 != c2" << std::endl;
    }
    if (c1 < c2) {
        std::cout << "c1 a un modulo plus petit que c2" << std::endl;
    }
    else if (c1 > c2) {
        std::cout << "c1 a un modulo plus grand que c2" << std::endl;
    }
    else {
        std::cout << "c1 et c2 on le meme modulo" << std::endl;
    }

    return 0;
}

//ajouter class avec une class public complexe et une class childcomplexecartesien ComplexeExponentiel etc etc
//ex class ComplexeExponentiel : public Complexe {
//comme ca on peut a la place de print exponentiel on peut vraiment retourner une class exponentiel avec son typre et ses private
//il faudrais juste caster avec ComplexeCartesien cx = *dynamic_cast<ComplexeCartesien*>(enCartesien()); enCartesien() c'est la methode de la classe qui va etre transformer
//normalement si on a tt les methode pour cout << + * ect pour chaque class on devrais pouvoir passer de l'un a l'autre facilement
//todo clean code
//-voir class global subclass
//-ducoup virtual pour pointer class global
//-post github
//main.hpp mais pas vraiment utile