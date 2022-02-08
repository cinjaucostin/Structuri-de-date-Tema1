#include "utils.h"

char cards[13] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

char carti[][52] = {
    "As",
    "Ah",
    "Ac",
    "Ad",
    "Ks",
    "Kh",
    "Kc",
    "Kd",
    "Qs",
    "Qh",
    "Qc",
    "Qd",
    "Js",
    "Jh",
    "Jc",
    "Jd",
    "Ts",
    "Th",
    "Tc",
    "Td",
    "9s",
    "9h",
    "9c",
    "9d",
    "8s",
    "8h",
    "8c",
    "8d",
    "7s",
    "7h",
    "7c",
    "7d",
    "6s",
    "6h",
    "6c",
    "6d",
    "5s",
    "5h",
    "5c",
    "5d",
    "4s",
    "4h",
    "4c",
    "4d",
    "3s",
    "3h",
    "3c",
    "3d",
    "2s",
    "2h",
    "2c",
    "2d"};

TList create(Item value) //functie de creare a unui nod
{
    TList nod;
    nod = (TList)malloc(sizeof(ListNode));
    nod->elem = value;
    nod->next = NULL;
    return nod;
}

TList initializare_pachet() //functia de initializare a pachetului
{
    TList pachet;
    pachet = create(carti[0]);
    for (int i = 1; i <= 51; i++)
    {
        pachet = insert_at_end(pachet, carti[i]); //inseram la sfarsit de fiecare data cate o carte
    }
    return pachet;
}

TList insert_at_end(TList head, Item value) //functie de inserare la sfarsit
{
    TList lista_aux, new_node;
    lista_aux = head;
    if (lista_aux == NULL)
    {
        new_node = create(value); //cazul in care nu exista niciun nod in lista
        return new_node;
    }
    else if (lista_aux->next == NULL) //inseamna ca lista are un singur element si va trebui sa inseram dupa acest element
    {
        new_node = create(value);
        lista_aux->next = new_node;
    }
    else //cazul in care lista are mai mult de un termen si trebuie sa o parcurgem pentru a introduce pe ultima pozitie
    {
        while (lista_aux->next != NULL)
        {
            lista_aux = lista_aux->next;
        }
        new_node = create(value);
        lista_aux->next = new_node;
    }
    return head;
}

TList insert_at_start(TList head, Item value) //functie de inserare la inceput unde cream un nou nod si ii facem legatura acestuia cu primul nod din lista
{
    TList new_node;
    new_node = create(value);
    new_node->next = head;
    return new_node;
}

TList copie_lista(TList head) //functie care copiaza o lista la o alta adresa de memorie(am folosit-o pentru n_piles)
{
    TList copie, lista_aux = head;
    copie = create(lista_aux->elem); //cream un nod nou cu primul element din lista
    lista_aux = lista_aux->next;
    while (lista_aux != NULL) //parcurgem lista initiala si la fiecare pas introducem la sfarsit un element din aceasta in noua noastra lista
    {
        copie = insert_at_end(copie, lista_aux->elem);
        lista_aux = lista_aux->next;
    }
    return copie;
}

TList inversare(TList head) //functia pentru amestecare de tip inversare
{
    TList list_aux = head->next;
    TList rlist = head;
    rlist->next = NULL;
    while (list_aux != NULL)
    {
        TList temp = list_aux;
        list_aux = list_aux->next;
        temp->next = rlist;
        rlist = temp;
    }
    return rlist;
}

TList amestecare_mongean(TList head) //amestecare de tip mongean(adaugam pe parcurs la inceput si la final din pachetul initial)
{
    int contor = 0;
    TList lista_mongean, lista_aux = head;
    lista_mongean = create(head->elem); //am creat o noua lista cu primul element din lista noastra initiala
    lista_aux = lista_aux->next;
    while (lista_aux != NULL)
    {
        if (contor % 2 == 0) //cazul in care contorul este numar par (inseamna ca trebuie sa introducem in stanga<->la inceputul listei)
            lista_mongean = insert_at_start(lista_mongean, lista_aux->elem);
        else if (contor % 2 == 1) //cazul in care contorul este numar impar (inseamna ca trebuie sa introducem in dreapta<->la sfarsitul listei)
            lista_mongean = insert_at_end(lista_mongean, lista_aux->elem);
        lista_aux = lista_aux->next;
        contor++;
    }
    freeTList(head);
    return lista_mongean;
}

TList intercalare(TList head) //functie pentru amestecare de tip intercalare
{
    TList list_aux1 = head, middle, ilist, list_aux2;
    int contor = 0;
    while (list_aux1 != NULL)
    {
        if (contor == length(head) / 2) //aflam pointerul de la mijlocul listei
        {
            middle = list_aux1;
            break;
        }
        contor++;
        list_aux1 = list_aux1->next;
    }
    list_aux1 = head;                //pointer cu care plecam de la inceputul listei
    ilist = create(list_aux1->elem); //noua lista pe care o vom returna
    list_aux1 = list_aux1->next;     //trecem la urmatorul element
    list_aux2 = middle;              //plecam cu o lista auxiliara de la mijlocul listei initiale
    while (list_aux2 != NULL)        //in principiu parcurgem simultan prima parte a listei si cea de-a doua parte a acesteia si introducem in noua lista
    {
        ilist = insert_at_end(ilist, list_aux2->elem);
        if (list_aux1 != middle)
            ilist = insert_at_end(ilist, list_aux1->elem);
        list_aux1 = list_aux1->next;
        list_aux2 = list_aux2->next;
    }
    freeTList(head);
    return ilist;
}

TList n_piles(TList head, int N, int *indici)
{
    TList lista_aux, pachet_nou;
    int dim_subpachet = length(head) / N, contor1 = 0, contor2 = 0;
    pachet_nou = create("dummy_cell"); //am creat un prim element in lista pentru a ma putea folosi de functia insert_at_end pe parcurs
    //deoarece aceasta functie necesita o lista creata deja in prealabil
    for (int i = 1; i <= N; i++)
    {
        for (lista_aux = head, contor1 = 0; lista_aux != NULL && contor1 <= length(head); lista_aux = lista_aux->next, contor1++)
        {
            if (contor1 % dim_subpachet == 0 && contor1 / dim_subpachet == indici[i] - 1) //verificam daca am ajuns la un multiplu de dim_supachet si
            //daca ne aflam la inceputul subpachetului pe care trebuie sa il introducem in noua lista
            {
                TList lista_aux_sec = copie_lista(lista_aux);
                TList temp = lista_aux_sec;
                contor2 = 0;
                while (contor2 < dim_subpachet) //introducerea subpachetului in noua lista
                {
                    pachet_nou = insert_at_end(pachet_nou, lista_aux_sec->elem);
                    lista_aux_sec = lista_aux_sec->next;
                    contor2++;
                }
                freeTList(temp); //eliberam memoria ocupata de lista copie
            }
        }
    }
    TList temp = pachet_nou; //stergem primul element din noua lista deoarece acesta este reprezentat de celula "dummy" de care nu avem nevoie
    pachet_nou = temp->next;
    free(temp); //eliberam memoria ocupata de acest nod
    freeTList(head);
    return pachet_nou;
}

TList amesteca(TList pachet, FILE *inputFile)
{
    int N;
    char *tip_amestecare, *nr_amestecari;
    tip_amestecare = malloc(100 * sizeof(char));
    nr_amestecari = malloc(10 * sizeof(char));
    fgets(nr_amestecari, 10, inputFile);
    N = atoi(nr_amestecari);
    free(nr_amestecari);
    for (int i = 0; i < N; i++)
    {
        fgets(tip_amestecare, 100, inputFile);
        if (strncmp(tip_amestecare, "mongean", strlen(tip_amestecare) - 2) == 0)
            pachet = amestecare_mongean(pachet);
        else if (strncmp(tip_amestecare, "inversare", strlen(tip_amestecare) - 2) == 0)
            pachet = inversare(pachet);
        else if (strncmp(tip_amestecare, "intercalare", strlen(tip_amestecare) - 2) == 0)
            pachet = intercalare(pachet);
        else if (strncmp(tip_amestecare, "npiles", 6) == 0)
        {
            char *token, delimitators[2] = " ";
            int *indici, k = 0;
            indici = malloc(15 * sizeof(int));
            token = strtok(tip_amestecare, delimitators); //ma folosesc de functia strtok pentru a afla indicii subpachetelor
            while (token != NULL)
            {
                if (isdigit(token[0]))
                {
                    indici[k] = atoi(token); //pentru a transforma numerele din char in int
                    k++;
                }
                token = strtok(NULL, delimitators);
            }
            pachet = n_piles(pachet, indici[0], indici);
            free(indici); //eliberam memoria ocupata de indici
            free(token);  //eliberam memoria ocupata de token
        }
    }
    free(tip_amestecare);
    return pachet;
}

TList deleteOnce(TList list, Item element) //functie de stergere a primului nod intalnit care are valoarea "element"
{
    TList itr = list, eliminat;
    if (strcmp(list->elem, element) == 0)
    {
        list = list->next; //aici trebuie dat un free(se pierde memorie)
        return list;
    }
    else if (strcmp(list->elem, element) == 1)
    {
        while (itr->next != NULL)
        {
            if (strcmp(itr->next->elem, element) == 0) //eliminam urmatorul element
            {
                eliminat = itr->next;
                itr->next = eliminat->next;
                free(eliminat);
                break;
            }
            itr = itr->next;
        }
    }
    return list;
}

void razboi(TList pachet, FILE *inputFile, FILE *outputFile)
{
    pachet = amesteca(pachet, inputFile);
    TList jucator1, jucator2, lista_aux = pachet;
    int contor = 0, nr_maini = 0, ok = 0;
    //Crearea celor doua pachete pentru cei doi jucatori
    while (lista_aux != NULL)
    {
        if (contor == 0)
        {
            jucator1 = create(lista_aux->elem);
        }
        else if (contor == 26)
        {
            jucator2 = create(lista_aux->elem);
        }
        lista_aux = lista_aux->next;
        contor++;
    }
    contor = 0;
    lista_aux = pachet;
    while (lista_aux != NULL)
    {
        if (contor >= 1 && contor <= 25)
        {
            jucator1 = insert_at_end(jucator1, lista_aux->elem);
        }
        else if (contor >= 27)
        {
            jucator2 = insert_at_end(jucator2, lista_aux->elem);
        }
        lista_aux = lista_aux->next;
        contor++;
    }
    while (nr_maini <= 99 && ok == 0) //while-ul care se opreste dupa 100 de maini(<=99 deoarece plecam cu nr_maini de la 0)
    {
        if (length(jucator1) == 0) //Daca primul jucator ramane fara carti inseamna ca al doilea a castigat
        {
            fprintf(outputFile, "2");
            ok = 1;
        }
        else if (length(jucator2) == 0) //Daca al doilea jucator ramane fara carti inseamna ca primul a castigat
        {
            fprintf(outputFile, "1");
            ok = 1;
        }
        else //inseamna ca ambii jucatori inca au carti
        {
            int carte_jucator1 = valoare_carte(jucator1->elem[0]), carte_jucator2 = valoare_carte(jucator2->elem[0]);
            if (carte_jucator1 > carte_jucator2) //inseamna ca trebuie sa luam cartea de la al 2 lea si s-o punem la primul
            {
                char *valoare1, *valoare2;
                valoare1 = malloc(5 * sizeof(char));
                valoare2 = malloc(5 * sizeof(char));
                strcpy(valoare1, jucator1->elem);
                strcpy(valoare2, jucator2->elem);
                jucator1 = deleteOnce(jucator1, valoare1);    //stergem cartea de schimb din pachetul primului jucator
                jucator2 = deleteOnce(jucator2, valoare2);    //stergem cartea de schimb din pachetul celui de-al doilea jucator
                jucator1 = insert_at_end(jucator1, valoare1); //inseram la sfarsitul primului pachet cartea de schimb primului jucator
                jucator1 = insert_at_end(jucator1, valoare2); //inseram la sfarsitul primului pachet cartea de schimb a celui de-al doilea jucator
                nr_maini++;                                   //marcam faptul ca a trecut o mana
            }
            else if (carte_jucator1 < carte_jucator2) //inseamna ca trebuie sa luam cartea de la primul si s-o punem la al 2 lea
            {
                //aici efectuam aceleasi operatii ca mai devreme doar ca schimbam destinatia cartilor
                char *valoare1, *valoare2;
                valoare1 = malloc(5 * sizeof(char));
                valoare2 = malloc(5 * sizeof(char));
                strcpy(valoare1, jucator1->elem);
                strcpy(valoare2, jucator2->elem);
                jucator1 = deleteOnce(jucator1, valoare1);
                jucator2 = deleteOnce(jucator2, valoare2);
                jucator2 = insert_at_end(jucator2, valoare2);
                jucator2 = insert_at_end(jucator2, valoare1);
                nr_maini++;
            }
            else if (carte_jucator1 == carte_jucator2) //cazul de razboi
            {
                int nr_carti_intoarse = 0, valoare_carte_razboi = valoare_carte(jucator1->elem[0]);
                //calculam numarul de carti intoarse dupa formula oferita in cerinta
                int min1 = min(length(jucator1), valoare_carte_razboi);
                int min2 = min(length(jucator2), valoare_carte_razboi);
                nr_carti_intoarse = min(min1, min2);
                TList de_introdus1, de_introdus2;
                de_introdus1 = primele_n_inversate(jucator1, nr_carti_intoarse);                 //cartile pe care trebuie sa le mutam din primul pachet
                de_introdus2 = primele_n_inversate(jucator2, nr_carti_intoarse);                 //cartile pe care trebuie sa le mutam din al doilea pachet
                jucator1 = sterge_primele_n(jucator1, nr_carti_intoarse);                        //stergem primele nr_carti_intoarse din pachetul primului jucator
                jucator2 = sterge_primele_n(jucator2, nr_carti_intoarse);                        //stergem primele nr_carti_intoarse din pachetul primului jucator
                if (valoare_carte(de_introdus1->elem[0]) > valoare_carte(de_introdus2->elem[0])) //partea celui de-al doilea jucator trebuie introdusa in primul pachet
                {
                    jucator1 = concatenare(jucator1, de_introdus1, de_introdus2, nr_carti_intoarse);
                    nr_maini++;
                }
                else if (valoare_carte(de_introdus1->elem[0]) < valoare_carte(de_introdus2->elem[0])) //partea primului jucator trebuie introdusa in pachetul celui de-al doilea
                {
                    jucator2 = concatenare(jucator2, de_introdus2, de_introdus1, nr_carti_intoarse);
                    nr_maini++;
                }
                //Eliberarea memoriei ocupate de listele auxiliare
                freeTList(de_introdus1);
                freeTList(de_introdus2);
            }
        }
    }
    if (ok == 0) //Inseamna ca nu s-a decis castigatorul dupa jucarea celor 100 de maini
    {
        int *frq1, *frq2;
        //realizam cate un vector de frecventa pentru fiecare pachet
        frq1 = frecventa_carti(jucator1);
        frq2 = frecventa_carti(jucator2);
        for (int i = 1; i <= 13; i++)
        {
            if (frq1[i] > frq2[i]) //inseamna ca primul jucator are mai multe carti cu valoare mai mare
            {
                fprintf(outputFile, "1 %c", cards[i - 1]);
                break;
            }
            else if (frq1[i] < frq2[i]) //inseamna ca al doilea jucator are mai multe carti cu o valoare mai mare
            {
                fprintf(outputFile, "2 %c", cards[i - 1]);
                break;
            }
        }
        //eliberam memoria ocupata de cei doi vectori de frecventa
        free(frq1);
        free(frq2);
    }
    //Eliberam memoria ocupata de pachetul initial si cele ale jucatorilor
    freeTList(pachet);
    freeTList(jucator2);
    freeTList(jucator1);
}

int *frecventa_carti(TList head) //functie cu ajutorul careia realizam vectorul de frecventa al unui pachet
{
    TList list = head;
    int *frecventa;
    frecventa = calloc(13, sizeof(int));
    while (list != NULL)
    {
        frecventa[rank_carte(list->elem[0])]++; //incrementam valoarea de pe pozitia rank_carte
        list = list->next;
    }
    return frecventa;
}

TList concatenare(TList head, TList list1, TList list2, int nr_carti_intoarse) //alaturam la head list1 si list2 cu ajutorul functiei de inserare la sfarsit
{
    int i = 0;
    TList parcurgere;
    parcurgere = list1;
    while (i <= nr_carti_intoarse && parcurgere != NULL)
    {
        head = insert_at_end(head, parcurgere->elem);
        parcurgere = parcurgere->next;
        i++;
    }
    i = 0;
    parcurgere = list2;
    while (i <= nr_carti_intoarse && parcurgere != NULL)
    {
        head = insert_at_end(head, parcurgere->elem);
        parcurgere = parcurgere->next;
        i++;
    }
    return head;
}

TList primele_n_inversate(TList head, int nr_carti_intoarse) //functie pentru a inversa primele n carti
{
    int i = 0;
    TList reversed, list = head;
    reversed = create(list->elem);
    list = list->next;
    while (i <= nr_carti_intoarse - 1 && list != NULL)
    {
        reversed = insert_at_start(reversed, list->elem);
        list = list->next;
        i++;
    }
    return reversed;
}

TList sterge_primele_n(TList head, int nr_carti_intoarse) //functie pentru a sterge primele n carti dintr-un pachet
{
    int i = 0;
    TList new_list, list = head;
    while (i <= nr_carti_intoarse && list != NULL)
    {
        new_list = deleteOnce(list, list->elem);
        list = list->next;
        i++;
    }
    return new_list;
}

void rollingstone(TList pachet, FILE *inputFile, FILE *outputFile)
{
    int contor = 0;
    TList jucator1, jucator2, jucator3, jucator4, list;
    int *frq1, *frq2, *frq3, *frq4;
    pachet = amesteca(pachet, inputFile);
    list = pachet;
    while (list != NULL)
    {
        if (contor == 0)
            jucator1 = create(list->elem);
        else if (contor == 13)
            jucator2 = create(list->elem);
        else if (contor == 26)
            jucator3 = create(list->elem);
        else if (contor == 39)
            jucator4 = create(list->elem);
        list = list->next;
        contor++;
    }
    list = pachet;
    contor = 0;
    while (list != NULL)
    {
        if (contor >= 1 && contor <= 12)
        {
            jucator1 = insert_at_end(jucator1, list->elem);
        }
        else if (contor >= 14 && contor <= 25)
        {
            jucator2 = insert_at_end(jucator2, list->elem);
        }
        else if (contor >= 27 && contor <= 38)
        {
            jucator3 = insert_at_end(jucator3, list->elem);
        }
        else if (contor >= 40)
        {
            jucator4 = insert_at_end(jucator4, list->elem);
        }
        contor++;
        list = list->next;
    }
    //Vom crea vectori de frecventa culorilor pentru fiecare pachet
    frq1 = frecventa_culori(jucator1);
    frq2 = frecventa_culori(jucator2);
    frq3 = frecventa_culori(jucator3);
    frq4 = frecventa_culori(jucator4);
    int mat[5][4]; //matrice in care vom aseza pe fiecare linie vectorii de frecventa ai culorilor pentru fiecare pachet
    //ultima linie va reprezenta vectorul de frecventa pentru culori pentru cartile care se afla pe masa
    for (int i = 0; i < 5; i++) //initializam elementele din matrice cu 0
    {
        for (int j = 0; j < 4; j++)
            mat[i][j] = 0;
    }
    //Introducem vectorii de frecventa pe fiecare linie
    for (int i = 0; i < 4; i++)
    {
        mat[0][i] = frq1[i];
    }
    for (int i = 0; i < 4; i++)
    {
        mat[1][i] = frq2[i];
    }
    for (int i = 0; i < 4; i++)
    {
        mat[2][i] = frq3[i];
    }
    for (int i = 0; i < 4; i++)
    {
        mat[3][i] = frq4[i];
    }
    int ok = 0, i = 0, j = 0;
    while (ok == 0)
    {
        //Conditiile de oprire:cazul in care un jucator ramane fara carti si castiga jocul
        if (win(mat[0]))
        {
            fprintf(outputFile, "1\n");
            ok = 1;
        }
        else if (win(mat[1]))
        {
            fprintf(outputFile, "2\n");
            ok = 1;
        }
        else if (win(mat[2]))
        {
            fprintf(outputFile, "3\n");
            ok = 1;
        }
        else if (win(mat[3]))
        {
            fprintf(outputFile, "4\n");
            ok = 1;
        }
        else if (mat[i][j] != 0) //cazul in care jucatorul cu pachetul pe linia i a matricei are carti de culoarea j
        {
            mat[i][j]--; //scadem o carte din culoarea j
            mat[4][j]++; //adaugam pe masa o carte din culoarea j
            if (i == 3)  //verificam daca i-ul este 3 asta inseamna ca ne aflam la ultimul jucator si trebuie sa ne intoarcem la primul
                i = 0;
            else
                i++; //inseamna ca trebuie sa mergem la jucatorul de pe linia i+1
        }
        else if (mat[i][j] == 0 && mat[4][j] != 0) //cazul in care jucatorul i nu mai are carti de culoarea j
        {
            mat[i][j] += mat[4][j]; //trebuie sa adaugam la campul culorii j ceea ce se afla pe masa(mutam cartile de culoare j de pe masa la jucatorul i in mana)
            mat[4][j] = 0;          //golim masa(resetam numarul cartilor de pe aceasta)
            if (j == 3)             //inseamna ca ne aflam la ultima culoare deci trebuie sa ne intoarcem la prima
                j = 0;
            else
                j++; //mergem la urmatoarea culoare
        }
        else if (mat[i][j] == 0 && mat[4][j] == 0) //cazul in care jucatorul i nu mai are carti de culoarea j si nici pe masa nu se afla nicio carte
        {
            //inseamna ca trebuie sa avansam la urmatoarea culoare dupa aceeasi regula(daca ne aflam la ultima mergem la prima, altfel avansam)
            if (j == 3)
                j = 0;
            else
                j++;
        }
    }
    //Eliberam toata memoria ocupata pe parcursul functiei
    freeTList(pachet);
    freeTList(jucator1);
    freeTList(jucator2);
    freeTList(jucator3);
    freeTList(jucator4);
    free(frq1);
    free(frq2);
    free(frq3);
    free(frq4);
}

int win(int *frq) //functie care ne ajuta sa stabilim un castigator la rolling_stone(cand jucatorul ramane fara nicio carte in pachet)
{
    if (frq[0] == 0 && frq[1] == 0 && frq[2] == 0 && frq[3] == 0)
        return 1;
    else
        return 0;
}

int *frecventa_culori(TList head) //functie care ne creeaza un vector de frecventa a pachetelor dupa culori
{
    int *frecventa;
    frecventa = calloc(5, sizeof(int));
    TList list = head;
    while (list != NULL)
    {
        if (list->elem[1] == 's')
            frecventa[0]++;
        else if (list->elem[1] == 'h')
            frecventa[1]++;
        else if (list->elem[1] == 'c')
            frecventa[2]++;
        else if (list->elem[1] == 'd')
            frecventa[3]++;
        list = list->next;
    }
    return frecventa;
}

int valoare_carte(char carte) //functie pentru a calcula valoarea unei carti
{
    int valoare;
    if (carte == 'A')
        valoare = 15;
    else if (carte == 'K')
        valoare = 14;
    else if (carte == 'Q')
        valoare = 13;
    else if (carte == 'J')
        valoare = 12;
    else if (carte == 'T')
        valoare = 10;
    else if (carte == '9')
        valoare = 9;
    else if (carte == '8')
        valoare = 8;
    else if (carte == '7')
        valoare = 7;
    else if (carte == '6')
        valoare = 6;
    else if (carte == '5')
        valoare = 5;
    else if (carte == '4')
        valoare = 4;
    else if (carte == '3')
        valoare = 3;
    else if (carte == '2')
        valoare = 2;
    return valoare;
}

int rank_carte(char carte) //functie pentru a calcula rank-ul unei carti
{
    int rank;
    if (carte == 'A')
        rank = 1;
    else if (carte == 'K')
        rank = 2;
    else if (carte == 'Q')
        rank = 3;
    else if (carte == 'J')
        rank = 4;
    else if (carte == 'T')
        rank = 5;
    else if (carte == '9')
        rank = 6;
    else if (carte == '8')
        rank = 7;
    else if (carte == '7')
        rank = 8;
    else if (carte == '6')
        rank = 9;
    else if (carte == '5')
        rank = 10;
    else if (carte == '4')
        rank = 11;
    else if (carte == '3')
        rank = 12;
    else if (carte == '2')
        rank = 13;
    return rank;
}

int min(int a, int b) //functie de minim
{
    if (a > b)
        return b;
    else
        return a;
}

int length(TList head) //functie de length
{
    TList iter = head;
    int nr = 0;
    while (iter != NULL)
    {
        iter = iter->next;
        nr++;
    }
    return nr;
}

TList freeTList(TList list) //functie de eliberare a memoriei ocupate de o lista
{
    TList next;
    while (list != NULL)
    {
        next = list;
        list = list->next;
        free(next);
    }
    return list;
}

void afisare_lista(TList head, FILE *output) //functie de afisare a unei liste intr-un fisier(am folosit-o pentru debugging)
{
    TList pachet = head;
    while (pachet != NULL)
    {
        fprintf(output, "%s ", pachet->elem);
        pachet = pachet->next;
    }
    fprintf(output, "\n");
}