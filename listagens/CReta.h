#ifndef CReta_H
#define CReta_H

#include <sstream>
#include <iomanip>
#include <fstream>
/// Class CReta,  representa uma reta y = a + b * x.
class CReta
{  
protected:
   double x = 0.0; ///< Representa valor de x.
   double y = 0.0; ///< Representa valor de y.
   double b = 0.0; ///< Representa valor de b da  equacao y = a + b*x; normalmente e calculado.
   double a = 0.0; ///< Representa valor de a da  equacao y = a + b*x; normalmente e calculado.
   
public:
  /// Construtor default.
  CReta ( ){ }
  /// Construtor sobrecarregado, recebe a e b.
  CReta (double _a, double _b): b{_b},a{_a}{ }

  /// Construtor sobrecarregado, recebe dados pontos (x1,y1) e (x2,y2).
  CReta (double x1, double y1, double x2, double y2) : b{(y2-y1)/(x2-x1)}, a{y1-b*x1} { }

  /// Construtor de copia.
  CReta( const CReta& reta): x{reta.x}, y{reta.y},a{reta.a}, b{reta.b} { }
  
  // Metodos Get/Set
  double X( )        { return x; }
  void X(double _x ) { x = _x;   }
  double Y( )        { return y; }
  void Y(double _y ) { y = _y;   }
  double A( )        { return a; }
  void A(double _a ) { a = _a;   }
  double B( )        { return b; }
  void B(double _b ) { b = _b;   }

  /// Calcula valor de y = Fx(x);
  virtual double Fx (double _x)       	{ x = _x; return y = a + b * x; }

  /// Calcula valor de y = Fx(x);
  double operator()(double x) 		{ return Fx(x); }

  /// Sobrecarga operador <<, permite uso cout << reta;
  friend std::ostream& operator<<( std::ostream& os, CReta& reta )  {
    os << "y = " << std::setw(10) << reta.a << " + " << std::setw(10) << reta.b << "*x ";
    return os;  }
  
  /// Sobrecarga operador >>, permite uso cin >> reta;
  friend std::istream& operator>>( std::istream& in, CReta& reta )  {
    in >> reta.a >> reta.b ;
    return in;  }
  
  /// Retorna string com a equacao y = a + b*x;
  std::string Equacao()   {    std::ostringstream os;     os << *this; 
    return os.str();  }
};
#endif //CReta_H
