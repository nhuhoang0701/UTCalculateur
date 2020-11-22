#include <iostream>
#include <cmath>
#include "exceptions.h"
#include "litterale_entiere.h"
#include "litterale_rationnelle.h"
#include "litterale_reelle.h"
#include "litterale_complexe.h"

LitteraleEntier::LitteraleEntier(int valeur) : valeur_{valeur}
{
    typeLitterale_ = TypeLitterale::ENTIER;
}

LitteraleNumerique *LitteraleEntier::cloneOnHeap() const
{
    return new LitteraleEntier(valeur_);
}

LitteraleNumerique *LitteraleEntier::puissance(LitteraleReelle &l)
{
    double valeur = std::pow(valeur_, l.getValeur());
    if (valeur == std::floor(valeur))
    {
        return new LitteraleEntier{static_cast<int>(std::pow(valeur_, l.getValeur()))};
    }
    return new LitteraleReelle{valeur};
}

LitteraleNumerique *LitteraleEntier::convertToNumerique(TypeLitterale type)
{
    switch (type)
    {
    case TypeLitterale::RATIONNEL:
        return new LitteraleRationnelle{valeur_, 1};
        break;
    case TypeLitterale::REEL:
        return new LitteraleReelle{valeur_, 0};
        break;
    default:
        return this;
        break;
    }
}

LitteraleNombre *LitteraleEntier::convertToComplexe()
{
    return new LitteraleComplexe{cloneOnHeap(), new LitteraleEntier{1}};
}

LitteraleNombre *LitteraleEntier::operator+(LitteraleNombre &l)
{
    if (l.getType() != TypeLitterale::ENTIER)
    {
        return LitteraleNumerique::operator+(l);
    }
    LitteraleEntier &l_cast = dynamic_cast<LitteraleEntier &>(l);
    return new LitteraleEntier{valeur_ + l_cast.valeur_};
}

LitteraleNombre *LitteraleEntier::operator-(LitteraleNombre &l)
{
    if (l.getType() != TypeLitterale::ENTIER)
    {
        return LitteraleNumerique::operator-(l);
    }
    LitteraleEntier &l_cast = dynamic_cast<LitteraleEntier &>(l);
    return new LitteraleEntier{valeur_ - l_cast.valeur_};
}

LitteraleNombre *LitteraleEntier::operator*(LitteraleNombre &l)
{
    if (l.getType() != TypeLitterale::ENTIER)
    {
        return LitteraleNumerique::operator*(l);
    }
    LitteraleEntier &l_cast = dynamic_cast<LitteraleEntier &>(l);
    return new LitteraleEntier{valeur_ * l_cast.valeur_};
}
LitteraleNombre *LitteraleEntier::operator/(LitteraleNombre &l)
{
    if (l.getType() != TypeLitterale::ENTIER)
    {
        return LitteraleNumerique::operator/(l);
    }
    LitteraleEntier &l_cast = dynamic_cast<LitteraleEntier &>(l);
    if (l_cast.isNull())
    {
        throw CalculateurException{"Impossible de divider à 0!"};
    }
    if (valeur_ % l_cast.valeur_ == 0)
    {
        return new LitteraleEntier{valeur_ / l_cast.valeur_};
    }
    else
    {
        return new LitteraleRationnelle{valeur_, l_cast.valeur_};
    }
}
