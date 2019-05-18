#ifndef ADDAPPLICANT_H
#define ADDAPPLICANT_H

#include <QDialog>

namespace Ui {
class AddApplicant;
}

class AddApplicant : public QDialog
{
    Q_OBJECT

public:
    explicit AddApplicant(QWidget *parent = nullptr);
    ~AddApplicant();

private:
    Ui::AddApplicant *ui;
};

#endif // ADDAPPLICANT_H
