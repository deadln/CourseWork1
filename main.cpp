#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
/*
 * ПЛАН
 * 1. Реализовать прием и отказ кандидатов(ГОТОВО)
 * 2. Реализовать функционал архива(ГОТОВО)
 * 3. Переделать вывод информации в полях с текстом чтобы исключить выход на рамки(ГОТОВО)
 * 4. Реализовать удаление лишних символов переноса строки из .txt файлов(ГОТОВО)
 * ДОПОЛНИТЕЛЬНО
 * 1. Реализовать работу с классификатором специальностей
 */
