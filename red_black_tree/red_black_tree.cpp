#include "tree.h"
#include "time.h"
#pragma warning (disable:4996)

static const char* menu[] =
{
	"1 - dodaj element",
	"2 - usun element",
	"3 - wyszukaj element",
	"4 - wyjdz"
};

void my_menu()
{
	for (int i = 0; i < 4; ++i)
	{
		printf("%s\n", menu[i]);
	}
}

void add_ele()
{
	int k;
	printf("Podaj liczbe: ");
	scanf("%d", &k);
	red_black_insert(k);
}

void delete_ele()
{
	int k;
	printf("Podaj liczbe do usuniecia:");
	scanf("%d", &k);

	node* search = tree_search(k);

	if (search)
		red_black_delete(search);
	
	else
	{
		printf("Podany element nie istnieje!");
		_sleep(2000);
	}
}

void search_ele()
{
	int k;
	printf("Podaj liczbe do wyszukania:");
	scanf("%d", &k);

	node* search = tree_search(k);

	if (search)
	{
		printf("Podany element istnieje!");
		_sleep(2000);
	}
	else
	{
		printf("Podany element nie istnieje!");
		_sleep(2000);
	}
		
}

int main()
{
	printf("DRZEWA CZARNO-CZERWONE \n");
	initialization();

	while (1)
	{
		print();
		my_menu();
		int opt;
		printf("Wybierz:");
		scanf("%d", &opt);

		switch (opt)
		{
		case 1:
			add_ele();
			break;
		case 2:
			delete_ele();
			break;
		case 3:
			search_ele();
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("Zla opcja!");
			_sleep(2000);
			break;
		}

		system("cls");
	}

}