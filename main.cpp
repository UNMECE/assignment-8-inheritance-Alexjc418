#include <iostream>
#include <cmath>

const double EPSILON_0 = 8.854e-12;
const double MU_0 = 4 * M_PI * 1e-7;

class Field {
protected:
    double *value;

public:
    Field(){ value = new double[3]{0.0, 0.0, 0.0}; }
    Field(double x, double y, double z){ value = new double[3]{x, y, z}; }
    Field(const Field &f){ value = new double[3]{f.value[0], f.value[1], f.value[2]}; }
    virtual ~Field(){ delete[] value; }

    virtual void printMagnitude(){
        std::cout << "Field Magnitude: " << std::sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2]) << std::endl;
    }

    Field& operator=(const Field &f){
        if (this != &f){
            value[0] = f.value[0];
            value[1] = f.value[1];
            value[2] = f.value[2];
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &out, const Field &f){
        out << "(" << f.value[0] << ", " << f.value[1] << ", " << f.value[2] << ")";
        return out;
    }
};

class Electric_Field : public Field {
private:
    double calculated_E;

public:
    Electric_Field() : Field(), calculated_E(0.0) {}
    Electric_Field(double ex, double ey, double ez) : Field(ex, ey, ez), calculated_E(0.0) {}
    Electric_Field(const Electric_Field &e) : Field(e), calculated_E(e.calculated_E) {}

    void calculateElectricField(double Q, double r){
        if (r != 0) calculated_E = Q / (4 * M_PI * EPSILON_0 * r * r);
        else calculated_E = 0;
    }

    Electric_Field operator+(const Electric_Field &e){
        return Electric_Field(value[0] + e.value[0], value[1] + e.value[1], value[2] + e.value[2]);
    }

    friend std::ostream& operator<<(std::ostream &out, const Electric_Field &e){
        out << "Electric Field: " << static_cast<const Field&>(e);
        return out;
    }

    void printCalculatedE(){
        std::cout << "Calculated Electric Field: " << calculated_E << " N/C" << std::endl;
    }
};

class Magnetic_Field : public Field {
private:
    double calculated_B;

public:
    Magnetic_Field() : Field(), calculated_B(0.0) {}
    Magnetic_Field(double bx, double by, double bz) : Field(bx, by, bz), calculated_B(0.0) {}
    Magnetic_Field(const Magnetic_Field &b) : Field(b), calculated_B(b.calculated_B) {}

    void calculateMagneticField(double I, double r){
        if (r != 0) calculated_B = I / (2 * M_PI * r * MU_0);
        else calculated_B = 0;
    }

    Magnetic_Field operator+(const Magnetic_Field &b){
        return Magnetic_Field(value[0] + b.value[0], value[1] + b.value[1], value[2] + b.value[2]);
    }

    friend std::ostream& operator<<(std::ostream &out, const Magnetic_Field &b){
        out << "Magnetic Field: " << static_cast<const Field&>(b);
        return out;
    }

    void printCalculatedB(){
        std::cout << "Calculated Magnetic Field: " << calculated_B << " T" << std::endl;
    }
};

int main(){
    Electric_Field E1(1e5, 10.9, 1.7e2);
    Magnetic_Field B1(2.5, 5.3, 7.1);

    E1.printMagnitude();
    B1.printMagnitude();

    E1.calculateElectricField(1e-6, 0.5);
    B1.calculateMagneticField(10, 0.2);

    E1.printCalculatedE();
    B1.printCalculatedB();

    Electric_Field E2(2.0, 3.0, 4.0);
    Electric_Field E3 = E1 + E2;
    std::cout << E3 << std::endl;

    Magnetic_Field B2(1.0, 2.0, 3.0);
    Magnetic_Field B3 = B1 + B2;
    std::cout << B3 << std::endl;

    return 0;
}

