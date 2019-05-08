#ifndef PROFILEDIALOG_HPP
#define PROFILEDIALOG_HPP
#include "../Wrapper/MhImageWrapper.hpp"

#include <QDialog>

namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ProfileDialog(Mh::ImageWrapper &&wrap, QWidget *parent = nullptr);
	~ProfileDialog();

	void updateProfile(const Mh::ImageWrapper& wrap);
	void updateDisplay();
private slots:
	void on_Discard_clicked();

	void on_Save_clicked();

private:
	Ui::ProfileDialog *ui;
	Mh::ImageWrapper preview;
	QPixmap image;
	float fmin,favg,fmax;
};

#endif // PROFILEDIALOG_HPP
