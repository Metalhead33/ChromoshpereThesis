#include "SharpenDialog.hpp"
#include "ui_SharpenDialog.h"

SharpenDialog::SharpenDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SharpenDialog)
{
	ui->setupUi(this);
}

SharpenDialog::~SharpenDialog()
{
	delete ui;
}
