#include "litterale_programme.h"

LitteraleNombre *LitteraleProgramme::evaluer()
{
    controleur_->traiterCommandBar(programme_.mid(1, programme_.length() - 2));
    std::cout << "nullptr in programme" << '\n';
    return nullptr;
}
