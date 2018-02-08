#include <iostream>

class complex {
    private:
        float real;
        float imag;

    public:
        complex();
        complex(const complex & src);
       ~complex();
        complex(float r,float i);
        
        float getReal() const;
        float getImag () const;
        void  setReal(float r);
        void  setImag(float i);
        void  print() const;

        complex operator+  (const complex & rhs) const;
        complex operator-  (const complex & rhs) const;
        complex operator*  (const complex & rhs) const;
        complex operator/  (const complex & rhs) const;
        bool    operator== (const complex & rhs) const;
     
        friend ostream& operator<<(ostream& os, const complex & c);
};
