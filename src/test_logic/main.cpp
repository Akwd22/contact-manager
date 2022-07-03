#include "unit_tests.h"
#include "date.h"
#include "contactmodel.h"

/// Démarrer un test concret de l'ensemble des classes et les relations.
void testGlobal()
{
    cout << "== DEBUT - TEST GLOBAL ==" << endl;

    Date dNow; dNow.setNow();

    // Création du contact.
    ContactModel c;
    c.setNom("Dupont");
    c.setPrenom("Jean");
    c.setEmail("jean.dupont@gmail.com");
    c.setPhoto("photo.png");
    c.setEntreprise("Google");
    c.setTel("0618961596");
    c.setDateModification(dNow);

    // Création des interactions du contact.
    string contenu1 =
            "Mon interaction\n\n"
            "@todo Format date 1 @date 01/10/2050\n"
            "@todo Format date 2 @date 1-10-2050\n"
            "Un autre commentaire\n"
            "Encore un autre commentaire @todo Sans date\n\n"
            " @todo Syntaxe@date 22/07/2045Un dernier commentaire ";

    string contenu2 = "@todo Appeler chef";

    InteractionModel i1(contenu1);
    InteractionModel i2(contenu2);
    i1.parseTodos();
    i2.parseTodos();

    c.getInteractions().add(i1);
    c.getInteractions().add(i2);

    // Afficher les informations du contact.
    cout << "#### Informations du contact ####" << endl;
    cout << c << endl;

    // Afficher les interactions du contact.
    cout << "#### Interactions du contact ####" << endl;
    for (auto & it1 : c.getInteractions().getList())
    {
        cout << "--- Interaction " << it1.getId() << endl;
        cout << it1 << endl;

        // Afficher les todos de l'interaction.
        cout << "--- Todos de l'interaction " << it1.getId() << endl;
        for (auto & it2 : it1.getTodos().getList())
        {
            cout << it2 << endl;
        }

        cout << "####" << endl;
    }

    cout << "== FIN - TEST GLOBAL ==" << endl;
}

int main()
{
    collectionUnitTests();          cout << endl;
    dateUnitTests();                cout << endl;
    todoModelUnitTests();           cout << endl;
    interactionModelUnitTests();    cout << endl;
    contactModelUnitTests();        cout << endl;
    testGlobal();                   cout << endl;

    return 0;
}
