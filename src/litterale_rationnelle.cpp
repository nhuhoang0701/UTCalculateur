#include <algorithm>

#include "exceptions.h"
#include "litterale_rationnelle.h"
#include "litterale_entiere.h"
#include "litterale_reelle.h"
#include "litterale_complexe.h"

LitteraleRationnelle::LitteraleRationnelle(int num, int den)
    : num_{num}, den_{den}
{
    if (den == 0)
    {
        throw CalculateurException("Den could not be 0!");
    }
    int gcd = std::__gcd(num_, den_);
    num_ /= gcd;
    den_ /= gcd;
    if (den_ < 0)
    {
        num_ *= -1;
        den_ *= -1;
    }
    typeLitterale_ = TypeLitterale::RATIONNEL;
}

const QString LitteraleRationnelle::affichage() const
{
    return QString::number(num_) + QString{"/"} + QString::number(den_);
}
LitteraleNumerique *LitteraleRationnelle::cloneOnHeap() const
{
    return new LitteraleRationnelle{num_, den_};
}

LitteraleNumerique *LitteraleRationnelle::simplifier()
{
    int gcd = std::__gcd(num_, den_);
    num_ /= gcd;
    den_ /= gcd;
    if (den_ < 0)
    {
        num_ *= -1;
        den_ *= -1;
    }
    if (den_ == 1)
    {
        return new LitteraleEntier{num_};
    }
    return this;
}

LitteraleNumerique *LitteraleRationnelle::convertToNumerique(TypeLitterale type)
{
    switch (type)
    {
    case TypeLitterale::ENTIER:
        if (den_ == 1)
            return new LitteraleEntier{num_};
        break;
    case TypeLitterale::REEL:
        return new LitteraleReelle{double(num_) / den_};
        break;
    }
    return this;
}

// LitteraleNombre *LitteraleRationnelle::convertToComplexe()
// {
//     return new LitteraleComplexe{cloneOnHeap(), new LitteraleEntier{}};
// }

LitteraleNumerique *LitteraleRationnelle::operator+(LitteraleNumerique &l)
{
    if (l.getType() != TypeLitterale::RATIONNEL)
    {
        return LitteraleNumerique::operator+(l);
    }
    LitteraleRationnelle &l_cast = dynamic_cast<LitteraleRationnelle &>(l);
    return (new LitteraleRationnelle{num_ * l_cast.getDen() + den_ * l_cast.getNum(), den_ * l_cast.getDen()})->simplifier();
}

LitteraleNumerique *LitteraleRationnelle::operator-(LitteraleNumerique &l)
{
    if (l.getType() != TypeLitterale::RATIONNEL)
    {
        return LitteraleNumerique::operator-(l);
    }
    LitteraleRationnelle &l_cast = dynamic_cast<LitteraleRationnelle &>(l);
    return (new LitteraleRationnelle{num_ * l_cast.getDen() - den_ * l_cast.getNum(), den_ * l_cast.getDen()})->simplifier();
}

LitteraleNumerique *LitteraleRationnelle::operator*(LitteraleNumerique &l)
{
    if (l.getType() != TypeLitterale::RATIONNEL)
    {
        return LitteraleNumerique::operator*(l);
    }
    LitteraleRationnelle &l_cast = dynamic_cast<LitteraleRationnelle &>(l);
    return (new LitteraleRationnelle{num_ * l_cast.getNum(), den_ * l_cast.getDen()})->simplifier();
}

LitteraleNumerique *LitteraleRationnelle::operator/(LitteraleNumerique &l)
{
    if (l.getType() != TypeLitterale::RATIONNEL)
    {
        return LitteraleNumerique::operator/(l);
    }
    LitteraleRationnelle &l_cast = dynamic_cast<LitteraleRationnelle &>(l);
    return (new LitteraleRationnelle{num_ * l_cast.getDen(), den_ * l_cast.getNum()})->simplifier();
}