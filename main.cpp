#include <iostream>
#include "Set.hpp"

void exibirMenu() {
    std::cout << "\n===== Menu de Conjunto =====\n";
    std::cout << "1. Inserir elemento\n";
    std::cout << "2. Remover elemento\n";
    std::cout << "3. Verificar se contém elemento\n";
    std::cout << "4. Mostrar elementos (in-order)\n";
    std::cout << "5. Mostrar árvore (formato gráfico)\n";
    std::cout << "6. Tamanho do conjunto\n";
    std::cout << "7. Está vazio?\n";
    std::cout << "8. Mínimo\n";
    std::cout << "9. Máximo\n";
    std::cout << "10. Sucessor de x\n";
    std::cout << "11. Predecessor de x\n";
    std::cout << "12. Clear\n";
    std::cout << "13. Swap entre dois conjuntos\n";
    std::cout << "14. União (A ∪ B)\n";
    std::cout << "15. Interseção (A ∩ B)\n";
    std::cout << "16. Diferença (A − B)\n";
    std::cout << "0. Sair\n";
    std::cout << "=========================\n";
}

Set* escolherConjunto(Set& A, Set& B, Set& C) {
    char c;
    std::cout << "Escolha o conjunto (A, B ou C): ";
    std::cin >> c;
    c = toupper(c);
    if (c == 'A') return &A;
    if (c == 'B') return &B;
    if (c == 'C') return &C;
    std::cout << "Conjunto inválido, selecione um válido, por favor.\n";
    return nullptr;
}

int main() {
    Set A, B, C;

    int opcao;
    do {
        exibirMenu();
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        Set *target = nullptr, *other = nullptr;
        int x;

        switch(opcao) {
            case 1:
                if ((target = escolherConjunto(A, B, C))) {
                    std::cout << "Digite o valor a inserir: ";
                    std::cin >> x;
                    target->insert(x);
                }
                break;
            case 2:
                if ((target = escolherConjunto(A, B, C))) {
                    std::cout << "Digite o valor a remover: ";
                    std::cin >> x;
                    target->remove(x);
                }
                break;
            case 3:
                if ((target = escolherConjunto(A, B, C))) {
                    std::cout << "Digite o valor a buscar: ";
                    std::cin >> x;
                    std::cout << (target->contains(x) ? "Está no conjunto.\n" : "Não está no conjunto.\n");
                }
                break;
            case 4:
                if ((target = escolherConjunto(A, B, C))) {
                    target->set_show();
                    std::cout << "\n";
                }
                break;
            case 5:
                if ((target = escolherConjunto(A, B, C))) {
                    target->show();
                }
                break;
            case 6:
                if ((target = escolherConjunto(A, B, C))) {
                    std::cout << "Tamanho: " << target->size() << "\n";
                }
                break;
            case 7:
                if ((target = escolherConjunto(A, B, C))) {
                    std::cout << (target->empty() ? "Está vazio.\n" : "Não está vazio.\n");
                }
                break;
            case 8:
                if ((target = escolherConjunto(A, B, C))) {
                    try {
                        std::cout << "Mínimo: " << target->minimum() << "\n";
                    } catch (std::exception& e) {
                        std::cerr << e.what() << "\n";
                    }
                }
                break;
            case 9:
                if ((target = escolherConjunto(A, B, C))) {
                    try {
                        std::cout << "Máximo: " << target->maximum() << "\n";
                    } catch (std::exception& e) {
                        std::cerr << e.what() << "\n";
                    }
                }
                break;
            case 10:
                if ((target = escolherConjunto(A, B, C))) {
                    std::cout << "Digite x: ";
                    std::cin >> x;
                    try {
                        std::cout << "Sucessor de " << x << ": " << target->succ(x) << "\n";
                    } catch (std::exception& e) {
                        std::cerr << e.what() << "\n";
                    }
                }
                break;
            case 11:
                if ((target = escolherConjunto(A, B, C))) {
                    std::cout << "Digite x: ";
                    std::cin >> x;
                    try {
                        std::cout << "Predecessor de " << x << ": " << target->pred(x) << "\n";
                    } catch (std::exception& e) {
                        std::cerr << e.what() << "\n";
                    }
                }
                break;
            case 12:
                if ((target = escolherConjunto(A, B, C))) {
                    target->clear();
                    std::cout << "Conjunto esvaziado.\n";
                }
                break;
            case 13:
                std::cout << "Escolha primeiro conjunto:\n";
                target = escolherConjunto(A, B, C);
                std::cout << "Escolha segundo conjunto:\n";
                other = escolherConjunto(A, B, C);
                if (target && other && target != other) {
                    target->swap(*other);
                    std::cout << "Conjuntos trocados.\n";
                } else {
                    std::cout << "Troca inválida.\n";
                }
                break;
            case 14: {
                Set *s1 = escolherConjunto(A, B, C);
                Set *s2 = escolherConjunto(A, B, C);
                if (s1 && s2) {
                    Set result = Set::union_between(*s1, *s2);
                    std::cout << "União: ";
                    result.set_show();
                    std::cout << "\n";
                }
                break;
            }
            case 15: {
                Set *s1 = escolherConjunto(A, B, C);
                Set *s2 = escolherConjunto(A, B, C);
                if (s1 && s2) {
                    Set result = Set::intersection(*s1, *s2);
                    std::cout << "Interseção: ";
                    result.set_show();
                    std::cout << "\n";
                }
                break;
            }
            case 16: {
                Set *s1 = escolherConjunto(A, B, C);
                Set *s2 = escolherConjunto(A, B, C);
                if (s1 && s2) {
                    Set result = Set::difference(*s1, *s2);
                    std::cout << "Diferença: ";
                    result.set_show();
                    std::cout << "\n";
                }
                break;
            }
            case 0:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção inválida.\n";
                break;
        }

    } while (opcao != 0);

    return 0;
}
