/**
 * file
 * date
 * author
 *
 * This document contains proprietary information belonging to mllapps.com.
 * Passing on and copying of this document, use and communication of its
 * contents is not permitted without prior written authorization.
 *
 * brief
 */
#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("About QRokBox Generator");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
