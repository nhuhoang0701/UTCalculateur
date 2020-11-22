#ifndef __LITTERALE_H__
#define __LITTERALE_H__

#include <memory>
#include <QString>

class LitteraleNombre;

enum class TypeLitterale
{
    ENTIER,
    RATIONNEL,
    REEL,
    COMPLEXE,
    EXPRESSION,
    PROGRAMME,
    NONE,
};

/*
** Litterale classe
*/
class Litterale
{
public:
    virtual ~Litterale() {}
    virtual const QString affichage(QString f = "") const = 0;
    virtual TypeLitterale getType() const { return typeLitterale_; }
    virtual bool isNull() const = 0;
    virtual LitteraleNombre *evaluer() = 0;
    virtual LitteraleNombre *cloneOnHeap() const = 0;

protected:
    TypeLitterale typeLitterale_;
};

class LitteraleNumerique;
class LitteraleReelle;
/*
** LitteraleNombre classe
*/
class LitteraleNombre : public Litterale
{
public:
    virtual bool isPos() const = 0;
    virtual LitteraleNombre *evaluer() override { return this; }
    virtual LitteraleNombre *simplifier() = 0;
    virtual LitteraleNombre *puissance(LitteraleReelle& l) = 0;
    virtual LitteraleNombre *convertToComplexe() = 0;

    virtual LitteraleNombre *operator+(LitteraleNombre &l) = 0;
    virtual LitteraleNombre *operator-(LitteraleNombre &l) = 0;
    virtual LitteraleNombre *operator*(LitteraleNombre &l) = 0;
    virtual LitteraleNombre *operator/(LitteraleNombre &l) = 0;
};

#include "litterale_complexe.h"
/*
** LitteraleNumerique classe compose LitteraleEntiere, LitteraleRationnelle, LitteraleReelle
*/
class LitteraleNumerique : public LitteraleNombre
{
    static LitteraleNumerique *a;
    static LitteraleNumerique *b;

public:
    // typedef LitteraleNumerique* (*fonc_t)(LitteraleNumerique&, LitteraleNumerique&);
    virtual LitteraleNombre *operator+(LitteraleNombre &l)
    {
        if (l.getType() != TypeLitterale::COMPLEXE)
        {
            LitteraleNumerique &l_cast = dynamic_cast<LitteraleNumerique &>(l);
            calculation(l_cast);
            return *a + *b;
        }
        else
        {
            return l + *this;
        }
    }
    virtual LitteraleNombre *operator-(LitteraleNombre &l)
    {
        if (l.getType() != TypeLitterale::COMPLEXE)
        {
            LitteraleNumerique &l_cast = dynamic_cast<LitteraleNumerique &>(l);
            calculation(l_cast);
            return *a - *b;
        }
        else
        {
            return l - *this;
        }
    }
    virtual LitteraleNombre *operator*(LitteraleNombre &l)
    {
        if (l.getType() != TypeLitterale::COMPLEXE)
        {
            LitteraleNumerique &l_cast = dynamic_cast<LitteraleNumerique &>(l);
            calculation(l_cast);
            return *a * *b;
        }
        else
        {
            return l * *this;
        }
    }
    virtual LitteraleNombre *operator/(LitteraleNombre &l)
    {
        if (l.getType() != TypeLitterale::COMPLEXE)
        {
            LitteraleNumerique &l_cast = dynamic_cast<LitteraleNumerique &>(l);
            calculation(l_cast);
            return *a / *b;
        }
        else
        {
            return l / *this;
        }
    }

    void calculation(LitteraleNumerique &l)
    {
        int typeMaxInt = std::max(static_cast<int>(getType()), static_cast<int>(l.getType()));
        TypeLitterale typeMax = static_cast<TypeLitterale>(typeMaxInt);
        a = convertToNumerique(typeMax);
        b = l.convertToNumerique(typeMax);
    }

    virtual LitteraleNumerique *cloneOnHeap() const = 0;
    virtual LitteraleNumerique *convertToNumerique(TypeLitterale type) = 0;
    // virtual double getValeur() const = 0;
    virtual LitteraleNumerique *simplifier() = 0;
    // virtual LitteraleNombre *convertToComplexe():
};

#endif // __LITTERALE_H__
