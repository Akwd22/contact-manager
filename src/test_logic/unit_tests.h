/**
 * @file unit_tests.h
 * @brief Fichier contenant les tests unitaires du projet.
 */

#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

/**
 * @def ASSERT_EXCEPTION(e, f, args...)
 * @brief Assertion pour vérifier si une exception est bien déclenchée.
 * @param e Classe de l'exception (ex. @a out_of_range).
 * @param f Fonction à appeler et à tester.
 * @param args Arguments de @a f.
 */
#define ASSERT_EXCEPTION(e, f, args...)         \
    {                                           \
        try                                     \
        {                                       \
            f(args);                            \
            assert(!#f #args #e "not thrown");  \
        }                                       \
        catch (e & e)                           \
        {                                       \
        }                                       \
        catch (exception & e)                   \
        {                                       \
            assert(!#f #args #e "not thrown");  \
        }                                       \
    }

/// Démarrer les tests unitaires de la classe @link Date @endlink.
void dateUnitTests();

/// Démarrer les tests unitaires de la classe @link TodoModel @endlink.
void todoModelUnitTests();

/// Démarrer les tests unitaires de la classe @link Collection @endlink.
void collectionUnitTests();

/// Démarrer les tests unitaires de la classe @link InteractionModel @endlink.
void interactionModelUnitTests();

/// Démarrer les tests unitaires de la classe @link ContactModel @endlink.
void contactModelUnitTests();

#endif // UNIT_TESTS_H
