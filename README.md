# Drzewa czerwono-czarne

```
Główny problem drzew wyszukiwań binarnych jest taki, że mogą w bardzo
prosty sposób stać się mocno niezbalansowane a w związku z tym czas operacji
na takim drzewie zwiększa się. Na przykład gdy w korzeniu drzewa umieścimy
1 i będziemy do niego dodawać elementy większe od 1 to prawa
strona będzie posiadać wszystkie dodane elementy, lewa będzie pusta a koszt
operacji na takim drzewie mogą być nawet tak duże jak w przypadku list.
```
```
Rozwiązaniem tego problemu są drzewa czarno-czerwone oraz drzewa
AVL dzięki którym drzewa przy pomocy odpowiednich algorytmów są w miarę
zbalansowane. Różnica pomiędzy wymienionymi drzewami jest taka, że w
przypadku drzewa AVL wykonuje się więcej swapów niż w drzewie czarno-
czerwonym, natomiast drzewo AVL jest nieco lepiej zbalansowane.
```
- Drzewa czerwono-czarne – mniej zamian, szybsze dodawanie, usuwanie węzłów.
- Drzewo AVL – lepiej zbalansowane drzewa, szybsze wyszukiwanie.

```
Zastosowanie drzew czerwono-czarnych możemy znaleźć w różnego
rodzaju strukturach danych, bazach danych, aplikacjach w których ważne jest
szybkie wyszukiwanie oraz w niektórych implementacjach C++.
```
```
Drzewo czarno czerwone jest drzewem wyszukiwań binarnych w
którym każdy węzeł jest koloru czarnego lub czerwonego. Jeśli drzewo jest
czerwono-czarne to posiada następujące własności:
```
- Każdy węzeł jest czerwony, albo czarny.
- Korzeń drzewa jest czarny.
- Każdy liść jest czarny.
- Jeśli węzeł jest czerwony, to obaj jego synowie muszą być czarni.
- Każda ścieżka prost z ustalonego węzła do liścia ma tyle samo czarnych węzłów.


![perfekcyjnie-zbalansowane](https://user-images.githubusercontent.com/85733696/180976157-603dc92c-6af7-408c-bda1-a72654f23a55.PNG)

_Rys.1 Drzewo BST – perfekcyjnie
zbalansowane_

![niezbalansowane](https://user-images.githubusercontent.com/85733696/180977054-6c00bef5-7cd1-4749-a200-1dc32063a0bf.PNG)

_Rys.2 Drzewo BST - niezbalansowane_


## ROTACJE:

```
Ponieważ operacje dodawania i usuwania węzłów z drzewa mogą
sprawić, że drzewo nie będzie spełniało warunków drzewa czerwono-czarnego,
dlatego aby spełniało odpowiednie warunki stosujemy algorytmy rotacji, w
algorytmach użyjemy wartownika do którego będą prowadziły wszystkie wskaźniki
węzłów nie mających prawego bądź lewego syna oraz rodzicem korzenia drzewa
będzie również wartownik:
```
- LEFT_ROTATE(x) → rotacja na drzewie względem węzła x
- RIGHT_ROTATE(x)
- T.nil – wartownik
- T.root – korzeń drzewa
- x – węzeł drzewa
- x.right – prawe poddrzewo węzła
- x.left – lewe poddrzewo węzła
- x.p – rodzic węzła

```
Lewą rotację na węźle wykonujemy wtedy gdy jego prawy syn nie jest
równy T.nil,
```
### LEFT_ROTATE(x)

```
if x.right != T.nil
    y = x.right
    x.right = y.left
    else y.left != T.nil
        y.left.p = x
    y.p = x.p
    if x.p == T.nil
        T.root = y
    elseif x == x.p.left
        x.p.left = y
    else
        x.p.right = y
    y.left = x
    x.p = y
```

### RIGHT_ROTATE(x)

```
y = x.left
x.left = y.right
if y.right != T.nil
    y.right.p = x
y.p = x.p
if y.p == T.nil
    T.root = y
elseif x == x.p.left
    x.p.left = y
else
    x.p.right = y
y.right = x
x.p = y
```
## WSTAWIANIE:

```
Wstawianie nowego węzła do drzewa czerwono czarnego o n węzłach
można wykonać w czasie O(lgn), wstawianie wykonuje się podobnie jak w przypadku
drzewa wyszukiwań binarnych. Na końcu wywołujemy funkcje, która koloruje i wykonuje
rotacje na węzłach aby zachować właściwości drzewa czerwono-czarnego:
```
- RED_BLACK_INSEERT(key) → Wstawia węzeł o podanym kluczu key
- RED_BLACK_INSERT_FIXUP(z) → Przywraca własności czerwonego drzewa, z
    to nowo powstały węzeł.
- z.key → miejsce do przechowywania klucza/danych w węźle

```
RED_BLACK_INSERT_FIXUP(z)
while z.p.color == RED
    if z.p == z.p.p.left
        if z.p.p.right.color == RED
        z.p.color = BLACK
        z.p.p.right.color = BLACK
        z.p.p.color = RED
        z = z.p.p
    else
        if z == z.p.right
               z = z.p
               LEFT_ROTATE(z)
        z.p.color = BLACK
        z.p.p.color = RED
        RIGHT_ROTATE(z.p.p)
else
    (to samo co po pierwszym if z zamienionymi wskaźnikami right i left)
T.root.color = BLACK
```

```
RED_BLACK_INSEERT(key)
z.key = key
z.color = RED
z.left = T.nil
z.right = T.nil
x = T.root
y = T.nil

while x != T.nil
    y = x
    if z.key < x.key
        x = x.left
    else
        x = x.right
if y == T.nil
    T.root = z
elseif z.key < y.key
    y.left = z
else
    y.right = z
z.p = y
RED_BLACK_INSERT_FIXUP(z)
```

## USUWANIE:

Podobnie jak dodawanie elementów operacja usuwania również wyko-
nuje się w czasie O(lgn). Przy usuwaniu elementów w drzewie użyjemy funkcji
RED_BLACK_TRANSPLANT(u,v), która wstawia jedno poddrzewo w miejsce
drugiego w jego ojcu.

```
RED_BLACK_TRANSPLANT(u, v)
if u.p == T.nil
    T.root = v
elseif u == u.p.left
    u.p.left = v
else
    u.p.right = v
v.p = u.p
```

Do usuwania użyjemy również funkcje TREE_MINIMUM(x), która
wyznacza wskaźnik do ostatniego elementu poddrzewa x.

```
TREE_MINIMUM(x)
while x.left != T.nill
    x = x.left
return x
```


Podczas wykonywania procedury RED_BLACK_DELETE(z), musimy
pamiętać, że gdy chcemy usunąć węzeł **z** mający mniej niż dwóch synów to z jest
usuwany z drzewa i chcemy, żeby węzłem **y** był **z**. Kiedy natomiast z ma dwóch
synów to węzłem **y** powinien zostać następnik **z** a **y** przemieszcza się na pozycje **z** w
drzewie. Podobnie jak w przypadku wstawiania po usunięciu węzła wywoływana jest
procedura RED_BLACK_DELETE_FIXUP(x), która przywraca własności drzewa
czerwono-czarnego.

```
RED_BLACK_DELETE(z)
y = z
yOriginalColor = y.color
if z.left == T.nil
    x = z.right
    RED_BLACK_TRANSPLANT(z, z.right)
elseif z.right ==T.nil
    x = z.left
    RED_BLACK_TRANSPLANT(z, z.left)
else
    y = TREE_MINIMUM(z.right)
    yOriginalColor = y.color
    x = y.right
    if y.p == z
        x.p = y
    else
        RED_BLACK_TRANSPLANT(y, y.right)
        y.right = z.right
        y.right.p = y
    RED_BLACK_TRANSPLANT(z, y)
    y.left = z.left
    y.left.p = y
    y.color = z.color
if yOriginalColor == BLACK
    RED_BLACK_DELETE_FIXUP(x)
```

Gdy usuwany węzeł był koloru czerwonego to po jego usunięciu własności
drzewa nadal są zachowane. Jeśli natomiast był czarne to rozważane są 4 przypadki:

- w (brat usuniętego węzła) jest czerwony
- w jest czarny i prawe i lewe dziecko jest czarne
- w jest czarny, prawe dziecko jest czarne i lewe czerwone
- w jest czarne, prawe dziecko czerwone i lewe czarne


```
RED_BLACK_DELETE_FIXUP(x)
while x != T.root i x.color == BLACK
    if x == x.p.left
        w = x.p.right
        if w.color == RED
            w.color = BLACK //PRZYPADEK 1
            x.p.color = RED //PRZYPADEK 1
            LEFT_ROTATE(x.p) //PRZYPADEK 1
            w = x.p.right //PRZYPADEK 1
        if x != T.nil i w.left.color == BLACK i w.right.color == BLACK
            w.color = RED //PRZYPADEK 2
            x.p.color = BLACK //PRZYPADEK 2
            x = x.p //PRZYPADEK 2
        else
            if x != T.nil i w.right.color == BLACK
                w.color = RED //PRZYPADEK 3
                w.left.color = BLACK //PRZYPADEK 3
                RIGHT_ROTATE(w) //PRZYPADEK 3
                w = x.p.right //PRZYPADEK 3
            if x != T.nil
                    w.color = x.p.color //PRZYPADEK 4
                    x.p.color = BLACK //PRZYPADEK 4
                    x.right.color = BLACK //PRZYPADEK 4
            LEFT_ROTATE(x.p) //PRZYPADEK 4
            x = T.root //PRZYPADEK 4
    else
        (to samo co po pierwszym if z zamienionymi wskaźnikami right i left)
x.color = BLACK
```
## WYSZUKIWANIE:

```
Operacje wyszukiwania w drzewie binarnym rozpoczynamy od korzenia,
kolejno porównując klucze i zagłębiając się w odpowiednie poddrzewo dopóki nie
trafimy na szukany klucz lub wartownik (T.nil).
```
```
k → szukany klucz

TREE_SEARCH(k)
x = T.root
while x!=T.nil i x.key != k
    if k<x.key
        x=x.left
    else
        x=x.right
if x == T.nil
    return NULL
else
    return x
```


```
Algorytm zwraca wartość NULL jeśli szukany element nie istnieje.
```
