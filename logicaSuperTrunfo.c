#include <stdio.h>
#include <string.h>

typedef struct {
    char codigo[10];
    char nome[50];
    char estado[30];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
} Carta;

float calcularDensidade(Carta c) {
    return c.populacao / c.area;
}

void cadastrarCarta(Carta *carta) {
    printf("\n--- Cadastro de Carta ---\n");
    printf("Código: ");
    scanf(" %[^\n]", carta->codigo);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", carta->nome);
    printf("Estado: ");
    scanf(" %[^\n]", carta->estado);
    printf("População: ");
    scanf("%d", &carta->populacao);
    printf("Área (km²): ");
    scanf("%f", &carta->area);
    printf("PIB (em bilhões): ");
    scanf("%f", &carta->pib);
    printf("Número de Pontos Turísticos: ");
    scanf("%d", &carta->pontosTuristicos);
}

void exibirCarta(Carta c) {
    printf("\n--- Carta: %s (%s) ---\n", c.nome, c.estado);
    printf("Código: %s\n", c.codigo);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", calcularDensidade(c));
}

int compararSimples(Carta c1, Carta c2, int atributo) {
    float v1, v2;

    switch (atributo) {
        case 1: v1 = c1.populacao; v2 = c2.populacao; break;
        case 2: v1 = c1.area; v2 = c2.area; break;
        case 3: v1 = c1.pib; v2 = c2.pib; break;
        case 4: v1 = c1.pontosTuristicos; v2 = c2.pontosTuristicos; break;
        case 5: v1 = calcularDensidade(c1); v2 = calcularDensidade(c2); break;
        default: return -1;
    }

    // Regra especial: densidade (menor vence)
    return (atributo == 5) ? (v1 < v2 ? 1 : (v1 > v2 ? 2 : 0)) : (v1 > v2 ? 1 : (v1 < v2 ? 2 : 0));
}

void nomeAtributo(int atributo) {
    switch (atributo) {
        case 1: printf("População"); break;
        case 2: printf("Área"); break;
        case 3: printf("PIB"); break;
        case 4: printf("Pontos Turísticos"); break;
        case 5: printf("Densidade Populacional"); break;
    }
}

void compararAvancado(Carta c1, Carta c2, int atr1, int atr2) {
    printf("\n📊 Comparando cartas com DOIS atributos...\n");

    int pontosC1 = 0, pontosC2 = 0;

    int r1 = compararSimples(c1, c2, atr1);
    printf("\n🔹 Atributo 1 - ");
    nomeAtributo(atr1);
    printf(": ");

    r1 == 1 ? (printf("%s venceu\n", c1.nome), pontosC1++) :
    r1 == 2 ? (printf("%s venceu\n", c2.nome), pontosC2++) :
             printf("Empate\n");

    int r2 = compararSimples(c1, c2, atr2);
    printf("🔸 Atributo 2 - ");
    nomeAtributo(atr2);
    printf(": ");

    r2 == 1 ? (printf("%s venceu\n", c1.nome), pontosC1++) :
    r2 == 2 ? (printf("%s venceu\n", c2.nome), pontosC2++) :
             printf("Empate\n");

    printf("\n✅ Resultado Final:\n");
    printf("%s: %d ponto(s)\n", c1.nome, pontosC1);
    printf("%s: %d ponto(s)\n", c2.nome, pontosC2);

    if (pontosC1 > pontosC2)
        printf("\n🏆 Vencedora: %s\n", c1.nome);
    else if (pontosC2 > pontosC1)
        printf("\n🏆 Vencedora: %s\n", c2.nome);
    else
        printf("\n🤝 Empate Final!\n");
}

void mostrarMenu() {
    printf("\nEscolha os atributos para comparação:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Populacional (menor vence)\n");
}

int main() {
    Carta carta1, carta2;
    int atr1, atr2;

    printf("🎮 SUPER TRUNFO DE CIDADES - Nível MESTRE\n");

    cadastrarCarta(&carta1);
    cadastrarCarta(&carta2);

    exibirCarta(carta1);
    exibirCarta(carta2);

    mostrarMenu();

    printf("\nDigite o número do 1º atributo: ");
    scanf("%d", &atr1);
    printf("Digite o número do 2º atributo: ");
    scanf("%d", &atr2);

    if ((atr1 < 1 || atr1 > 5) || (atr2 < 1 || atr2 > 5)) {
        printf("\n❌ Atributo inválido!\n");
        return 1;
    }

    compararAvancado(carta1, carta2, atr1, atr2);

    return 0;
}

