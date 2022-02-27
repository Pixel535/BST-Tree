#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define COUNT 10

typedef struct drzewo
{
    int numer;
    struct drzewo *lwezel;
    struct drzewo *pwezel;
}drzewo;

int losuj(int min, int max)
{
	return (rand()%(max-min+1)+min);
}

bool CzyJestCale(drzewo **bst,int i, int iloscwezlow);

void Add(drzewo **bst, int n)
{
    if((*bst) == NULL)
    {
        drzewo *nowe;
        nowe = (drzewo*)malloc(sizeof(drzewo));
        nowe -> numer = n;
        nowe -> lwezel = NULL;
        nowe -> pwezel = NULL;
       *bst = nowe;
    }
    else
    {
        if ((*bst)->numer > n)
        {
            Add(&((*bst)->lwezel), n);
        }
        else if((*bst)->numer < n)
        {
            Add(&(*bst)->pwezel, n);
        }
        else
        {
            printf("\nWartosc juz istnieje\n");
        }
    }
}

int minValueNode(drzewo **bst)
{
    drzewo* current = (*bst);
    while (current && current->lwezel != NULL)
        current = current->lwezel;

    return current;
}

int Del(drzewo **bst, int numer)
{
    if((*bst) != NULL)
    {
            if ((*bst) == NULL)
            return (*bst);

        if (numer < (*bst)->numer)
            (*bst)->lwezel = Del(&(*bst)->lwezel, numer);

        else if (numer > (*bst)->numer)
            (*bst)->pwezel = Del(&(*bst)->pwezel, numer);

        else {
            if ((*bst)->lwezel == NULL) {
                drzewo* temp = (*bst)->pwezel;
                free((*bst));
                return temp;
            }
            else if ((*bst)->pwezel == NULL) {
                drzewo* temp = (*bst)->lwezel;
                free((*bst));
                return temp;
            }

            drzewo* temp = minValueNode(&(*bst)->pwezel);

            (*bst)->numer = temp->numer;

            (*bst)->pwezel = Del(&(*bst)->pwezel, temp->numer);
        }
        return (*bst);
    }
    else
    {
        printf("Nie ma takiego elementu\n\n");
    }
}


void Show(drzewo *bst, int space)
{
    space += COUNT;
    if ((bst) == NULL)
    {
         return;
    }
    else
    {
        Show(bst->pwezel, space);
        printf("\n");
        for (int i = COUNT; i < space; i++)
        {
            printf(" ");
        }
        printf("%d\n", bst->numer);
        Show(bst->lwezel, space);
    }

}

void ShowLVR(drzewo **bst)
{
    if((*bst) == NULL)
    {
        printf("Drzewo jest puste\n");
    }
    else{
    if ((*bst)->lwezel != NULL)
    {
        ShowLVR(&((*bst)->lwezel));
    }
    printf("%d ",(*bst)->numer);
    if ((*bst)->pwezel != NULL)
    {
        ShowLVR(&((*bst)->pwezel));
    }
    }
}

void ShowVLR(drzewo **bst)
{
     if((*bst) == NULL)
     {
        printf("Drzewo jest puste\n");
     }
     else{
     printf("%d ",(*bst)->numer);
     if ((*bst)->lwezel != NULL)
     {
        ShowVLR(&((*bst)->lwezel));
     }
     if ((*bst)->pwezel != NULL)
     {
        ShowVLR(&((*bst)->pwezel));
     }
     }
}

void ShowLRV(drzewo **bst)
{
     if((*bst) == NULL)
     {
        printf("Drzewo jest puste\n");
     }
     else{
     if ((*bst)->lwezel != NULL)
     {
        ShowLRV(&((*bst)->lwezel));
     }
     if ((*bst)->pwezel != NULL)
     {
        ShowLRV(&((*bst)->pwezel));
     }
     printf("%d ",(*bst)->numer);
     }
}


int height(drzewo **bst)
{
    if ((*bst) == NULL)
        return 0;
    else {

        int lheight = height(&(*bst)->lwezel);
        int rheight = height(&(*bst)->pwezel);

        if (lheight > rheight)
            return (lheight+1);

        else
            return (rheight+1);
    }
}

void ShowLVO(drzewo **bst)
{
    if((*bst) == NULL)
     {
        printf("Drzewo jest puste\n");
     }
     else{
    int h = height(&(*bst));
    h--;
    int i;
    for (i = 0; i <= h; i++)
        printCurrentLevel(&(*bst), i);
     }
}

void printCurrentLevel(drzewo **bst, int level)
{
    if ((*bst) == NULL)
        return;
    if (level == 0)
        printf("%d ", (*bst)->numer);
    else if (level > 0) {
        printCurrentLevel(&(*bst)->lwezel, level - 1);
        printCurrentLevel(&(*bst)->pwezel, level - 1);
    }
}

int NodesAtLevel(drzewo **bst, int level)
{
        if((*bst)==NULL)
                return 0;
        if(level==0)
                return 1;
        return NodesAtLevel(&(*bst)->lwezel,level-1) + NodesAtLevel(&(*bst)->pwezel,level-1);
}

bool CzyKopiec(drzewo **bst)
{
    int iloscwezlow = counter(&(*bst));
    int i = 0;

    if (CzyJestCale(&(*bst), i, iloscwezlow))
        return true;
    return false;
}

bool CzyJestCale(drzewo **bst,int i, int iloscwezlow)
{
    if ((*bst) == NULL)
        return (true);

    if (i >= iloscwezlow)
        return (false);

    return (CzyJestCale(&(*bst)->lwezel, 2 * i + 1, iloscwezlow) && CzyJestCale(&(*bst)->pwezel, 2 * i + 2, iloscwezlow));
}




int counter(drzewo **bst)
{
    if ((*bst) == NULL)
        return (0);
    return (1 + counter(&(*bst)->lwezel) + counter(&(*bst)->pwezel));
}

void Tablicowa(drzewo **bst)
{
    if((*bst) == NULL)
     {
        printf("Drzewo jest puste\n");
     }
     else{
    int h = height(&(*bst));
    h--;
    int i;
    for (i = 0; i <= h; i++)
        printCurrentLevel2(&(*bst), i);
     }
}

void printCurrentLevel2(drzewo **bst, int level)
{
    if ((*bst) == NULL)
        return;
    if (level == 0)
        printf("|%d|", (*bst)->numer);
    else if (level > 0) {
        printCurrentLevel2(&(*bst)->lwezel, level - 1);
        printCurrentLevel2(&(*bst)->pwezel, level - 1);
    }
}

int main()
{
    srand(time(NULL));
    drzewo *bst = NULL;
    int komenda;
    int n,k;
	while(1)
    {
        printf("Program Drzewa BST\n");
        printf("----------------------------------------------\n");
        printf("[0] Wyjscie z programu\n");
        printf("[1] Dodaj wezel\n");
        printf("[2] Usun wezel\n");
        printf("[3] Wyswietl drzewo - graficznie\n");
        printf("[4] Inorder - LVR\n");
        printf("[5] Preorder - VLR\n");
        printf("[6] Postorder - LRV\n");
        printf("[7] Level order\n");
        printf("[8] Wysokosc\n");
        printf("[9] Ilosc wezlow na danym poziomie\n");
        printf("[10] Czy jest kopcem ?\n");
        printf("[11] Reprezentacja tablicowa\n");
        printf("----------------------------------------------\n\n");
		printf("\nWybrana komenda: ");
		scanf("%d", &komenda);
		printf("\n");
		switch (komenda)
		{
			case 0: return 0; break;
			case 1:
			    {
			        printf("Podaj ile liczb chesz dodac: ");
			        scanf("%d", &k);
			        for(int i = 0; i<k; i++)
                    {
                        n = losuj(1,100);
                        Add(&bst, n);
                    }
                    system("pause");
                    system("cls");
			        break;
			    }

			case 2:
			    {
			        printf("Podaj wartosc jaka chcesz usunac: ");
                    scanf("%d", &n);
                    printf("----------------------------------------------\n\n");
                    printf("Drzewo przed usunieciem:\n\n");
                    Show(bst, 10);
                    printf("########################################################\n\n");
                    Del(&bst, n);
                    printf("########################################################\n\n");
                    printf("Drzewo po usunieciu:\n\n");
                    Show(bst, 10);
                    printf("----------------------------------------------\n\n");
			        system("pause");
                    system("cls");
			        break;
			    }

			case 3:
			    {
			        Show(bst, 10);
			        printf("\n");
			        system("pause");
                    system("cls");
			        break;
			    }

			case 4:
			    {
			        ShowLVR(&bst);
			        printf("\n");
			        system("pause");
                    system("cls");
                    break;
			    }
            case 5:
			    {
			        ShowVLR(&bst);
			        printf("\n");
			        system("pause");
                    system("cls");
                    break;
			    }
            case 6:
			    {
			        ShowLRV(&bst);
			        printf("\n");
			        system("pause");
                    system("cls");
                    break;
			    }
            case 7:
			    {
			        ShowLVO(&bst);
			        printf("\n");
			        system("pause");
                    system("cls");
                    break;
			    }
            case 8:
			    {
			        height(&bst);
			        printf("Wysokosc jest rowna: %d\n", (height(&bst)-1));
			        system("pause");
                    system("cls");
                    break;
			    }
            case 9:
			    {
			        int lvl;
			        if((bst) == NULL)
                    {
                       printf("Drzewo jest puste\n");
                    }
                    else
                    {
                        printf("Podaj poziom ktory mam sprawdzic: ");
                        scanf("%d", &lvl);
                        NodesAtLevel(&bst, lvl);
                        printf("Liczba wezlow na poziomie [%d] jest rowna: %d\n", lvl, NodesAtLevel(&bst, lvl));
                    }
                    printf("\n");
                    system("pause");
                    system("cls");
                    break;
			    }
            case 10:
			    {
			        if((bst) == NULL)
                    {
                       printf("Drzewo jest puste\n");
                    }
                    else
                    {
                        if(CzyKopiec(&bst) == true)
                        {
                            printf("Ma strukture kopca!\n");
                        }
                        else
                        {
                            printf("Nie ma struktury kopca!\n");
                        }
                    }
                    printf("\n");
                    system("pause");
                    system("cls");
                    break;
			    }
            case 11:
			    {
                    if(CzyKopiec(&bst) == true)
                    {
                        Tablicowa((&bst));
                    }
                    else
                    {
                        printf("Nie ma struktury kopca!\n");
                    }
                    printf("\n");
                    system("pause");
                    system("cls");
                    break;
			    }

        }
    }

    return 0;
}
//Mateusz Gajda Grupa WCY20IY2S1
