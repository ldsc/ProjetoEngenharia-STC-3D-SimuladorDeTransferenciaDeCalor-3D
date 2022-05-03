#ifndef CSegmentoReta_h
#define CSegmentoReta_h

#include <iomanip> 
#include <vector>

#include "CReta.h"

/// Class CSegmentoReta, representa uma reta com intervalo xmin->xmax.
class CSegmentoReta : public CReta 
{
private:
   double xmin = 0.0; ///< Inicio do segmento de reta.
   double xmax = 0.0; ///< Fim do segmento de reta.
   bool ok = false;     ///< Se verdadeiro, x usado esta dentro intervalo válido (xmin->xmax) 

public:
  /// Construtor default.
  CSegmentoReta ( ) { }
  
  /// Construtor sobrecarregado, recebe pontos (x1,y1), (x2,y2).
  CSegmentoReta (double x1, double y1, double x2, double y2)
    :CReta(x1,y1,x2,y2),xmin{x1},xmax{x2} { TestarIntervalo(x1); }
    
  /// Construtor copia.
  CSegmentoReta (const CSegmentoReta& segmento )  :CReta() {
    x = segmento.x;     y = segmento.y; a = segmento.a; b = segmento.b;
    xmin = segmento.xmin;  xmax = segmento.xmax;   ok = segmento.ok;
  }

  // Metodos Get/Set
  double Xmin( )           { return xmin;  }
  void Xmin(double _xmin ) { xmin = _xmin; }
  double Xmax( )           { return xmax;  }
  void Xmax(double _xmax ) { xmax = _xmax; }
  
  /// Se retorno for verdadeiro, valor de y esta dentro intervalo xmin->xmax.
  bool Ok()                { return ok; }
  
  /// Verifica se esta no intervalo de xmin->xmax.
  bool TestarIntervalo (double _x)   { return ok = ( _x >= xmin and _x <= xmax)? 1:0;  }
  
  /// Calcula valor de y = Fx(x);
  virtual double Fx (double _x)  {   
    TestarIntervalo(_x);
    return CReta::Fx(_x);
  }
  
  /// Calcula valor de y = Fx(x);
  double operator()(double _x) { return Fx(_x); }

  /// Sobrecarga operador <<, permite uso cout << reta;
  friend std::ostream& operator<<( std::ostream& os, const CSegmentoReta& segmento )  {
    os.precision(10); 
    os<< segmento.xmin << " -> " << segmento.xmax
      << " : y = "<< std::setw(15) << std::setprecision(10) << segmento.a << " + "
      << std::setw(15) << std::setprecision(10) << segmento.b << "*x ";
    return os;
  }
  
  /// Sobrecarga operador >>, permite uso cin >> reta;
  friend std::istream& operator>>( std::istream& in, CSegmentoReta& segmento  )  {
   in >> segmento.xmin >> segmento.xmax
      >> segmento.a >> segmento.b;
   return in;
  }

  friend class CInterpolacaoLinear;
};
#endif //CSegmentoReta_h
