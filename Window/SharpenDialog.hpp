#ifndef SHARPENDIALOG_HPP
#define SHARPENDIALOG_HPP

#include <QDialog>

namespace Ui {
class SharpenDialog;
}

class SharpenDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SharpenDialog(QWidget *parent = nullptr);
	~SharpenDialog();

private:
	Ui::SharpenDialog *ui;
};

#endif // SHARPENDIALOG_HPP
