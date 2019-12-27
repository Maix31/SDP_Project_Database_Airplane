# SDP_Project_Database_Airplane
Проект по СДП практикум.

Проектът разделям на 2 части, реализация на база данни и CLI.
За удобство информацията от Planes.db се зарежда в работната памет(динамичен масив) и 
при излизане се сериализира обратно във файла. Операции за търсене, променяне и триене
са със сложност O(n), ако преди това не е извикана команда optimize, след което 
сложността вече е O(logn). Това се постига със сортиране на информацията по Id и
използване на Binary-Search.
CLI - Недовършен.

Класовете използвани за решението са Database и CLI.
Database използва std::vector за боравене на данните.
Съдържа булева променлива sorted, която казва дали е сортирана информацията.
Методите са create, delete, update, show, optimize, search.
search се ползва в create, delete, update за намирането на самолета.

Идеи за бъдещи подобрения:
Използване на хеш-таблица, която от id дава показател към самолета в файла,
Това ще свали сложността за намиране до О(1) и като бонус, тъй като вече няма
да има нужда от optimize да сортира информацията, самолетите вкарани в системата
ще бъдат в хронологичен ред без допълнително работа.
Недостатък e, че изисква повече памет.

