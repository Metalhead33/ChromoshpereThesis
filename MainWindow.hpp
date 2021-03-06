#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_compose2img_clicked();

	void on_editImg_clicked();

	void on_profileImage_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
