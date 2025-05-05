#include <iostream>
#include "Set.hpp"
#include <vector>
#include <unistd.h>
#include <fstream>

void exibirMenu()
{
    std::cout << "\n===== Menu de Conjunto =====\n";
    std::cout << "help -> ajuda\n";
    std::cout << "create -> Criar conjunto\n";
    std::cout << "insert (conjunto) -> Inserir elementos\n";
    std::cout << "remove (conjunto) (elemento) -> Remover elemento\n";
    std::cout << "contains (conj) (elem) -> Verificar se contém elemento\n";
    std::cout << "set-show (conj) -> Mostrar elementos (in-order)\n";
    std::cout << "tree-show (conj) -> Mostrar árvore (formato gráfico)\n";
    std::cout << "size (conj) -> Tamanho do conjunto\n";
    std::cout << "empty (conj) -> Está vazio?\n";
    std::cout << "min (conj) -> Mínimo\n";
    std::cout << "max (conj) -> Máximo\n";
    std::cout << "succ (conj) (x) -> Sucessor de x\n";
    std::cout << "pred (conj) (x) -> Predecessor de x\n";
    std::cout << "clear (conj) -> Clear\n";
    std::cout << "swap (A) (B) -> Swap entre dois conjuntos\n";
    std::cout << "union (A) (B) -> União (A u B)\n";
    std::cout << "intersection (A) (B) -> Interseção (A ∩ B)\n";
    std::cout << "diff (A) (B) -> Diferença (A - B)\n";
    std::cout << "save (conj) (filename) -> Salvar conjunto\n";
    std::cout << "load (filename) -> carregar conjunto\n";
    std::cout << "exit -> Sair\n";
    std::cout << "=========================\n";
}

std::vector<Set*> sets;
Set* generator = new Set();

Set *escolherConjunto()
{
    size_t index;
    std::cin >> index;

    if (index >= sets.size())
    {
        throw std::runtime_error("Set not found.");
    }

    return sets[index];
}

int main()
{
    std::cout << "Regulators open..." << std::endl;
    sleep(1);
    std::cout << "All trees are seeded..." << std::endl;
    sleep(1);
    std::cout << "Ready... Set... Go!" << std::endl;
    sleep(1);

    std::cout << "Set manager on! Type help to get more instructions." << std::endl;

    std::string opcao;
    do
    {
        std::cout << "command => ";
        std::cin >> opcao;
        Set *conj = nullptr;
        Set *sec_conj = nullptr;

        if (opcao == "create")
        {
            sets.push_back(new Set());
            std::cout << "New set created at index " << sets.size() - 1 << std::endl;
        }
        else if (opcao == "insert")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                std::cout << "How many elements will be added? ";
                int how_many;
                std::cin >> how_many;

                while (how_many--)
                {
                    int s;
                    std::cin >> s;
                    conj->insert(s);
                }

                std::cout << "Set updated!" << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "remove")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                std::cout << "What to remove? ";
                int s;
                std::cin >> s;
                conj->remove(s);
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "contains")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                std::cout << "Which element to check? ";
                int s;
                std::cin >> s;
                std::cout << (conj->contains(s) ? "Yes, it is in the set." : "No, it's not in the set.") << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "set-show")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                conj->set_show();
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "tree-show")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                conj->show();
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "size")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                std::cout << "Size: " << conj->size() << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "empty")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                std::cout << (conj->empty() ? "It's empty!" : "It's not empty!") << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "min")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                std::cout << "Minimum: " << conj->minimum() << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "max")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                std::cout << "Maximum: " << conj->maximum() << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "succ")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                std::cout << "Which number? ";
                int s;
                std::cin >> s;
                std::cout << "Successor: " << conj->succ(s) << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "pred")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                std::cout << "Which number? ";
                int s;
                std::cin >> s;
                std::cout << "Predecessor: " << conj->pred(s) << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "clear")
        {
            std::cout << "Which set will be selected? ";
            try
            {
                conj = escolherConjunto();
                conj->clear();
                std::cout << "Set was cleared." << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "swap")
        {
            std::cout << "Which sets will be selected? ";
            try
            {
                conj = escolherConjunto();
                sec_conj = escolherConjunto();
                if (conj != sec_conj)
                {
                    conj->swap(*sec_conj);
                    std::cout << "Sets swapped!" << std::endl;
                }
                else
                {
                    std::cout << "Cannot swap the same set." << std::endl;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "union")
        {
            std::cout << "Select the two sets: ";
            try
            {
                conj = escolherConjunto();
                sec_conj = escolherConjunto();
                if (conj != sec_conj)
                {
                    Set* result = new Set(Set::union_between(*conj, *sec_conj));
                    std::cout << "Sets united!" << std::endl;
                    result->set_show();
                    sets.push_back(result);
                    std::cout << "set created at index " << sets.size() << std::endl;
                }
                else
                {
                    std::cout << "Cannot union the same set with itself." << std::endl;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "intersection")
        {
            std::cout << "Select the two sets: ";
            try
            {
                conj = escolherConjunto();
                sec_conj = escolherConjunto();
                if (conj != sec_conj)
                {
                    Set* result = new Set(Set::intersection(*conj, *sec_conj));
                    std::cout << "Intersection created!" << std::endl;
                    result->set_show();
                    sets.push_back(result);
                    std::cout << "set created at index " << sets.size() << std::endl;
                    
                }
                else
                {
                    std::cout << "Cannot intersect the same set with itself." << std::endl;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        } else if(opcao == "diff") {
            std::cout << "Select the two sets: ";
            try
            {
                conj = escolherConjunto();
                sec_conj = escolherConjunto();
                if (conj != sec_conj)
                {
                    Set* result = new Set(Set::difference(*conj, *sec_conj));
                    std::cout << "Difference calculated!" << std::endl;
                    result->set_show();
                    sets.push_back(result);
                    std::cout << "set created at index " << sets.size() << std::endl;
                }
                else
                {
                    std::cout << "Cannot diff the same set with itself." << std::endl;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "help")
        {
            exibirMenu();
        }
        else if (opcao == "save")
        {
            std::cout << "Which set to save? ";
            try
            {
                conj = escolherConjunto();
                std::cout << "Filename: ";
                std::string nome;
                std::cin >> nome;
                conj->save(nome);
                std::cout << "Set saved!\n";
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
                std::cin.clear(); 
                std::cin.ignore(10000, '\n');
            }
        }
        else if (opcao == "load")
        {
            std::cout << "Filename to load: ";
            std::string nome;
            std::cin >> nome;
            Set *novo = new Set();
            novo->load(nome);
            sets.push_back(novo);
            std::cout << "Set loaded at index " << sets.size() - 1 << "\n";
        }

        std::cout << std::endl;
    } while (opcao != "exit");
}