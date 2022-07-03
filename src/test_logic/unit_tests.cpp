#include <assert.h>
#include <iostream>
#include <string>

#include "unit_tests.h"
#include "collection.h"
#include "contactmodel.h"
#include "date.h"
#include "interactionmodel.h"
#include "todomodel.h"

using namespace std;

void dateUnitTests()
{
    cout << "== DEBUT - Test Classe Date ==" << endl;

    cout << "TEST - constructors" << endl;
    {
        Date dNull;
        assert(dNull.isNull());

        ASSERT_EXCEPTION(domain_error, Date, 1, 1, 3001);
        ASSERT_EXCEPTION(domain_error, Date, 1, 1, 1969);
        ASSERT_EXCEPTION(domain_error, Date, 0, 1, 1970);
        ASSERT_EXCEPTION(domain_error, Date, 32, 1, 1970);
        ASSERT_EXCEPTION(domain_error, Date, 1, 0, 1970);
        ASSERT_EXCEPTION(domain_error, Date, 1, 13, 1970);

        Date dCustom1(22, 7, 2000);
        Date dCustom2(dCustom1);
        assert(!dCustom1.isNull());
        assert(dCustom1 == dCustom2);
    }

    cout << "TEST - comparison operators" << endl;
    {
        Date dNull;
        Date dNow; dNow.setNow();
        Date dCustom1(22, 7, 2000);
        Date dCustom2; dCustom2.fromDate(22, 7, 2000);

        assert(dCustom1 == dCustom2);
        assert(dCustom1 != dNow);
        assert(dCustom1 < dNow);
        assert(dNow > dCustom1);
        assert(dCustom1 <= dCustom2);
        assert(dCustom2 >= dCustom1);
        assert(dCustom1 <= dNow);
        assert(dNow >= dCustom1);
        assert(dNull < dNow);
    }

    cout << "TEST - Date::setNow()" << endl;
    {
        Date dNow; dNow.setNow();

        struct tm tmNow;
        time_t nNow = time(0);
        tmNow = *localtime(&nNow);

        assert(dNow.getJour() == (unsigned int)tmNow.tm_mday && dNow.getMois() == (unsigned int)tmNow.tm_mon + 1 && dNow.getAnnee() == (unsigned int)tmNow.tm_year + 1900);
    }

    cout << "TEST - Date::toString()" << endl;
    {
        Date dNull;
        assert(dNull.toString() == "");

        Date dCustom1(22, 7, 2000);
        assert(dCustom1.toString() == "22/7/2000");
    }

    cout << "TEST - Date::fromString()" << endl;
    {
        Date dCustom1;

        ASSERT_EXCEPTION(domain_error, dCustom1.fromString, "01/01/3001");
        ASSERT_EXCEPTION(domain_error, dCustom1.fromString, "01/01/1969");
        ASSERT_EXCEPTION(domain_error, dCustom1.fromString, "00/01/1970");
        ASSERT_EXCEPTION(domain_error, dCustom1.fromString, "32/01/1970");
        ASSERT_EXCEPTION(domain_error, dCustom1.fromString, "01/00/1970");
        ASSERT_EXCEPTION(domain_error, dCustom1.fromString, "01/13/1970");
        ASSERT_EXCEPTION(invalid_argument, dCustom1.fromString, "date");

        dCustom1.fromString("22/07/2000");
        assert(dCustom1.toString() == "22/7/2000");

        dCustom1.fromString("22-7-2000");
        assert(dCustom1.toString() == "22/7/2000");
    }

    cout << "TEST - Date::setNull()" << endl;
    {
        Date dCustom1(22, 7, 2000);
        dCustom1.setNull();

        assert(dCustom1.isNull());
    }

    cout << "TEST - Date::getJour() - Date::getMois() - Date::getAnnee()" << endl;
    {
        Date dNull;
        assert(!dNull.getJour());
        assert(!dNull.getMois());
        assert(!dNull.getAnnee());

        Date dCustom1(22, 7, 2000);
        assert(dCustom1.getJour() == 22);
        assert(dCustom1.getMois() == 7);
        assert(dCustom1.getAnnee() == 2000);
    }

    cout << "TEST - Date::isNull()" << endl;
    {
        Date dNull;
        assert(dNull.isNull());

        Date dCustom1(22, 7, 2000);
        assert(!dCustom1.isNull());
    }

    cout << "TEST - Date::setDate()" << endl;
    {
        Date dCustom1;
        Date dCustom2(22, 7, 2000);

        struct tm tm;
        time_t n = time(0);
        tm = *localtime(&n);
        tm.tm_hour = 12;
        tm.tm_mday = 22;
        tm.tm_mon = 6;
        tm.tm_year = 100;
        dCustom1.setDate(tm);

        assert(dCustom1 == dCustom2);
    }

    cout << "TEST - Date::fromDate()" << endl;
    {
        Date dCustom1;

        ASSERT_EXCEPTION(domain_error, dCustom1.fromDate, 1, 1, 3001);
        ASSERT_EXCEPTION(domain_error, dCustom1.fromDate, 1, 1, 1969);
        ASSERT_EXCEPTION(domain_error, dCustom1.fromDate, 0, 1, 1970);
        ASSERT_EXCEPTION(domain_error, dCustom1.fromDate, 32, 1, 1970);
        ASSERT_EXCEPTION(domain_error, dCustom1.fromDate, 1, 0, 1970);
        ASSERT_EXCEPTION(domain_error, dCustom1.fromDate, 1, 13, 1970);

        dCustom1.fromDate(22, 7, 2000);
        assert(dCustom1.toString() == "22/7/2000");
    }

    cout << "TEST - Date::operator=()" << endl;
    {
        Date dNull;
        Date dCustom1(22, 7, 2000);
        Date dCopy;

        dCopy = dCustom1;
        assert(dCopy == dCustom1);

        dCopy = dNull;
        assert(dCopy == dNull);
    }

    cout << "TEST - Date::operator<<() --> ";
    {
        Date dNow; dNow.setNow();
        cout << "Date du jour : " << dNow << endl;
    }

    cout << "== FIN - Test Classe Date ==" << endl;
}

void todoModelUnitTests()
{
    cout << "== DEBUT - Test Classe TodoModel ==" << endl;

    TodoModel::idCount = 1;

    cout << "TEST - constructors" << endl;
    {
        Date dNull;
        Date dNow; dNow.setNow();
        Date dCustom1(22, 7, 2000);

        TodoModel t1("Texte");
        assert(t1.getId() == TodoModel::idCount - 1);
        assert(t1.getResume() == "Texte");
        assert(t1.getDateTodo() == dNow);

        TodoModel t2(1, dCustom1, "Texte");
        assert(t2.getId() == 1);
        assert(t2.getResume() == "Texte");
        assert(t2.getDateTodo() == dCustom1);

        TodoModel t3(t1);
        assert(t1 == t3);

        ASSERT_EXCEPTION(invalid_argument, TodoModel, "");
        ASSERT_EXCEPTION(invalid_argument, TodoModel, 1, dCustom1, "");
        ASSERT_EXCEPTION(invalid_argument, TodoModel, 1, dNull, "Texte");
    }

    cout << "TEST - comparison operators" << endl;
    {
        Date dCustom1(22, 7, 2000);

        TodoModel t1(1, dCustom1, "Texte 1");
        TodoModel t2(1, dCustom1, "Texte 1");
        TodoModel t3(1, dCustom1, "Texte 2");

        assert(t1 == t2);
        assert(t1 != t3);
    }

    cout << "TEST - TodoModel::operator=()" << endl;
    {
        Date dCustom1(22, 7, 2000);

        TodoModel t1("Texte 1");
        TodoModel t2("Texte 2");

        t1 = t2;

        assert(t1 == t2);
    }

    cout << "TEST - TodoModel::getId() - TodoModel::getDateTodo() - TodoModel::getResume()" << endl;
    {
        Date dCustom1(22, 7, 2000);

        TodoModel t1(1, dCustom1, "Texte 1");

        assert(t1.getId() == 1);
        assert(t1.getDateTodo() == dCustom1);
        assert(t1.getResume() == "Texte 1");
    }

    cout << "TEST - TodoModel::setDateTodo()" << endl;
    {
        Date dNull;
        Date dCustom1(22, 7, 2000);

        TodoModel t1("Texte 1");
        t1.setDateTodo(dCustom1);

        assert(t1.getDateTodo() == dCustom1);

        ASSERT_EXCEPTION(invalid_argument, t1.setDateTodo, dNull);
    }

    cout << "TEST - TodoModel::setResume()" << endl;
    {
        TodoModel t1("Texte");
        t1.setResume("Texte 1");

        assert(t1.getResume() == "Texte 1");

        ASSERT_EXCEPTION(invalid_argument, t1.setResume, "");
    }

    cout << "TEST - TodoModel::operator<<() --> ";
    {
        TodoModel t1(1, Date(22, 7, 2000), "Texte 1");
        cout << t1 << endl;
    }

    cout << "== FIN - Test Classe TodoModel ==" << endl;
}

void collectionUnitTests()
{
    cout << "== DEBUT - Test Classe Collection ==" << endl;

    cout << "TEST - constructors" << endl;
    {
        Collection<string> c;
        assert(!c.count());
    }

    cout << "TEST - Collection::getIndex()" << endl;
    {
        Collection<string> c;

        c.add("T1");
        c.add("T2");

        assert(c.getIndex(0) == "T1");
        assert(c.getIndex(1) == "T2");

        ASSERT_EXCEPTION(out_of_range, c.getIndex, 2);
    }

    cout << "TEST - Collection::add()" << endl;
    {
        Collection<string> c;
        c.add("T1");
        c.add("T1");
        c.add("T2");

        assert(c.getIndex(0) == "T1");
        assert(c.getIndex(1) == "T1");
        assert(c.getIndex(2) == "T2");
        assert(c.count() == 3);
    }

    cout << "TEST - Collection::remove()" << endl;
    {
        Collection<string> c;

        c.add("T1");
        c.add("T1");
        c.add("T2"),
        c.remove("T1");

        assert(c.count() == 1 && c.getIndex(0) == "T2");
    }

    cout << "TEST - Collection::clear()" << endl;
    {
        Collection<string> c;

        c.add("T1");
        c.add("T2");
        c.clear();

        assert(!c.count());
    }

    cout << "TEST - Collection::count()" << endl;
    {
        Collection<string> c;

        assert(!c.count());

        c.add("T1");

        assert(c.count() == 1);
    }

    cout << "TEST - comparison operators" << endl;
    {
        Collection<string> c1;
        Collection<string> c2;
        Collection<string> c3;

        c1.add("T1");
        c2.add("T1");
        c3.add("T2");

        assert(c1 == c2);
        assert(c1 != c3);
    }

    cout << "TEST - Collection::operator<<() --> " << endl;
    {
        Collection<string> c1;
        c1.add("Texte 1");
        c1.add("Texte 2");
        c1.add("Texte 3");

        cout << c1 << endl;
    }

    cout << "== FIN - Test Classe Collection ==" << endl;
}

void interactionModelUnitTests()
{
    cout << "== DEBUT - Test Classe InteractionModel ==" << endl;

    InteractionModel::idCount = 1;

    cout << "TEST - constructors" << endl;
    {
        Date dNull;
        Date dNow; dNow.setNow();
        Date dCustom1(22, 7, 2000);

        InteractionModel i1("Texte");
        assert(i1.getId() == InteractionModel::idCount - 1);
        assert(i1.getContenu() == "Texte");
        assert(i1.getDateInteraction() == dNow);
        assert(!i1.getTodos().count());

        InteractionModel i2(1, dCustom1, "Texte");
        assert(i2.getId() == 1);
        assert(i2.getContenu() == "Texte");
        assert(i2.getDateInteraction() == dCustom1);
        assert(!i2.getTodos().count());

        InteractionModel i3(i1);
        assert(i1 == i3);

        ASSERT_EXCEPTION(invalid_argument, InteractionModel, "");
        ASSERT_EXCEPTION(invalid_argument, InteractionModel, 1, dCustom1, "");
        ASSERT_EXCEPTION(invalid_argument, InteractionModel, 1, dNull, "Texte");
    }

    cout << "TEST - comparison operators" << endl;
    {
        Date dCustom1(22, 7, 2000);

        InteractionModel i1(1, dCustom1, "Texte 1");
        InteractionModel i2(1, dCustom1, "Texte 1");
        InteractionModel i3(1, dCustom1, "Texte 2");

        TodoModel m1("Texte 1");
        TodoModel m2(m1);
        TodoModel m3("Texte 2");

        i1.getTodos().add(m1);
        i2.getTodos().add(m2);
        i3.getTodos().add(m3);

        assert(i1 == i2);
        assert(i1 != i3);
    }

    cout << "TEST - InteractionModel::operator=()" << endl;
    {
        Date dCustom1(22, 7, 2000);

        InteractionModel i1("Texte 1");
        InteractionModel i2("Texte 2");

        i1 = i2;

        assert(i1 == i2);
    }

    cout << "TEST - InteractionModel::getId() - InteractionModel::getDateInteraction() - InteractionModel::getContenu()" << endl;
    {
        Date dCustom1(22, 7, 2000);

        InteractionModel i1(1, dCustom1, "Texte 1");

        assert(i1.getId() == 1);
        assert(i1.getDateInteraction() == dCustom1);
        assert(i1.getContenu() == "Texte 1");
    }

    cout << "TEST - InteractionModel::setContenu()" << endl;
    {
        InteractionModel i1("Texte");
        i1.setContenu("Texte 1");

        assert(i1.getContenu() == "Texte 1");

        ASSERT_EXCEPTION(invalid_argument, i1.setContenu, "");
    }

    cout << "TEST - InteractionModel::parseTodos()" << endl;
    {
        Date dNow; dNow.setNow();

        // Parse du contenu de l'interaction,
        // pour créer les instances TodoModel.
        string contenu =
                "Mon interaction\n\n"
                "@todo Format date 1 @date 01/10/2050\n"
                "@todo Format date 2 @date 1-10-2050\n"
                "Un autre commentaire\n"
                "Encore un autre commentaire @todo Sans date\n\n"
                " @todo Syntaxe@date 22/07/2045Un dernier commentaire ";

        InteractionModel i(contenu);
        i.parseTodos();

        // Vérification du bon parsing et de la bonne
        // création des instances TodoModel.
        TodoCollection c = i.getTodos();
        TodoModel t1 = c.getIndex(0);
        TodoModel t2 = c.getIndex(1);
        TodoModel t3 = c.getIndex(2);
        TodoModel t4 = c.getIndex(3);

        assert(t1.getResume() == "Format date 1" && t1.getDateTodo() == Date(1, 10, 2050));
        assert(t2.getResume() == "Format date 2" && t2.getDateTodo() == Date(1, 10, 2050));
        assert(t3.getResume() == "Sans date" && t3.getDateTodo() == dNow);
        assert(t4.getResume() == "Syntaxe" && t4.getDateTodo() == Date(22, 7, 2045));
    }

    cout << "TEST - TodoModel::operator<<() --> " << endl;
    {
        InteractionModel i1(1, Date(22, 7, 2000), "Texte 1");
        i1.getTodos().add(TodoModel("Texte"));

        cout << i1 << endl;
    }

    cout << "== FIN - Test Classe InteractionModel ==" << endl;
}

void contactModelUnitTests()
{
    // Remplir un contact avec des données de test.
    auto donneesTest = [](ContactModel & contact)
    {
        contact.setNom("Dupont");
        contact.setPrenom("Jean");
        contact.setEmail("jean.dupont@gmail.com");
        contact.setTel("0618961596");
        contact.setEntreprise("Google");
        contact.setPhoto("photo.png");
        contact.setDateModification(Date(1, 1, 2500));
        contact.getInteractions().add(InteractionModel(1, Date(22, 7, 2000), "Texte 1"));
    };

    cout << "== DEBUT - Test Classe ContactModel ==" << endl;

    ContactModel::idCount = 1;

    cout << "TEST - static default" << endl;
    {
        assert(ContactModel::idCount == 1);
        assert(ContactModel::getDateSuppression().isNull());
    }

    cout << "TEST - static ContactModel::setDateSuppression()" << endl;
    {
        Date dCustom1(22, 7, 2000);
        Date dCustom2(21, 7, 2000);

        ContactModel::setDateSuppression(dCustom1);
        assert(ContactModel::getDateSuppression() == dCustom1);

        ASSERT_EXCEPTION(invalid_argument, ContactModel::setDateSuppression, dCustom2);
    }

    cout << "TEST - static ContactModel::getDateSuppression()" << endl;
    {
        Date dCustom1(22, 7, 2000);

        ContactModel::setDateSuppression(dCustom1);
        assert(ContactModel::getDateSuppression() == dCustom1);
    }

    cout << "TEST - constructors" << endl;
    {
        Date dNull;
        Date dNow; dNow.setNow();
        Date dCustom1(22, 7, 2000);

        ContactModel c1;
        assert(c1.getId() == ContactModel::idCount - 1);
        assert(c1.getDateModification().isNull());
        assert(c1.getDateCreation() == dNow);
        assert(!c1.getInteractions().count());

        ContactModel c2(1, dCustom1);
        assert(c2.getId() == 1);
        assert(c2.getDateCreation() == dCustom1);
        assert(c2.getDateModification().isNull());
        assert(!c2.getInteractions().count());

        donneesTest(c1);
        ContactModel c3(c1);
        assert(c1 == c3);

        ASSERT_EXCEPTION(invalid_argument, ContactModel, 1, dNull);
    }

    cout << "TEST - comparison operators" << endl;
    {
        Date dCustom1(22, 7, 2000);

        ContactModel c1(1, dCustom1);
        donneesTest(c1);

        ContactModel c2(1, dCustom1);
        donneesTest(c2);

        ContactModel c3(1, dCustom1);

        assert(c1 == c2);
        assert(c1 != c3);
    }

    cout << "TEST - InteractionModel::operator=()" << endl;
    {
        Date dCustom1(22, 7, 2000);

        ContactModel c1;
        ContactModel c2(1, dCustom1);
        donneesTest(c2);

        c1 = c2;

        assert(c1 == c2);
    }

    cout << "TEST - setters and getters" << endl;
    {
        Date dCustom1(22, 7, 2000);

        ContactModel c1(1, dCustom1);
        donneesTest(c1);

        assert(c1.getId() == 1);
        assert(c1.getDateCreation() == dCustom1);
        assert(c1.getNom() == "Dupont");
        assert(c1.getPrenom() == "Jean");
        assert(c1.getEmail() == "jean.dupont@gmail.com");
        assert(c1.getTel() == "0618961596");
        assert(c1.getEntreprise() == "Google");
        assert(c1.getPhoto() == "photo.png");
        assert(c1.getDateModification() == Date(1, 1, 2500));
        assert(c1.getInteractions().getIndex(0) == InteractionModel(1, dCustom1, "Texte 1"));
    }

    cout << "TEST - ContactModel::setEmail()" << endl;
    {
        ContactModel c1;

        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, ".user@example.org");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "user.@example.org");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "us..er@example.org");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "Abc.example.com");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "A@b@c@example.com");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "a\"b(c)d,e:f;g<h>i[j\\k]l@example.com");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "just\\\"not\\\"right@example.com");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "this is\\\"not\\allowed@example.com");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "this\\ still\\\"not\\\\allowed@example.com");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "1234567890123456789012345678901234567890123456789012345678901234+x@example.com");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "i_like_underscore@but_its_not_allowed_in_this_part.example.com");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "QA[icon]CHOCOLATE[icon]@test.com");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "\\\" \\\"@example.org");
        ASSERT_EXCEPTION(invalid_argument, c1.setEmail, "\\\"john..doe\\\"@example.org");

        c1.setEmail("");
        c1.setEmail("simple@example.com");
        c1.setEmail("very.common@example.com");
        c1.setEmail("disposable.style.email.with+symbol@example.com");
        c1.setEmail("other.email-with-hyphen@example.com");
        c1.setEmail("fully-qualified-domain@example.com");
        c1.setEmail("user.name+tag+sorting@example.com");
        c1.setEmail("x@example.com");
        c1.setEmail("example-indeed@strange-example.com");
        c1.setEmail("test/test@test.com");
        c1.setEmail("admin@mailserver1");
        c1.setEmail("example@s.example");
        c1.setEmail("mailhost!username@example.org");
        c1.setEmail("user%example.com@example.org");
    }

    cout << "TEST - ContactModel::setDateModification()" << endl;
    {
        ContactModel c1;

        ASSERT_EXCEPTION(invalid_argument, c1.setDateModification, Date(1, 1, 1970)); // dateModification < dateCreation

        c1.setDateModification(Date(2, 1, 2500));

        ASSERT_EXCEPTION(invalid_argument, c1.setDateModification, Date(1, 1, 2500)); // dateModificationNew < dateModificationOld
    }

    cout << "TEST - ContactModel::setTel()" << endl;
    {
        ContactModel c1;

        ASSERT_EXCEPTION(invalid_argument, c1.setTel, "téléphone");
        ASSERT_EXCEPTION(invalid_argument, c1.setTel, "06 18 96 15 96");
        ASSERT_EXCEPTION(invalid_argument, c1.setTel, "06.18.96.15.96");

        c1.setTel("");
        c1.setTel("0618961596");
        c1.setTel("+33618961596");
        c1.setTel("5214");
    }

    cout << "TEST - ContactModel::operator<<() --> ";
    {
        ContactModel c1;
        donneesTest(c1);

        cout << c1 << endl;
    }

    cout << "== FIN - Test Classe ContactModel ==" << endl;
}
