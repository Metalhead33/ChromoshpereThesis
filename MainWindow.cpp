#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "Io/StdStream.hpp"
#include "ImgClassifier/ProfileImage.hpp"
#include <stdexcept>
#include "Window/ImageAdjuster.hpp"
#include "Window/ProfileDialog.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_compose2img_clicked()
{
	try {
	auto fileName1 = QFileDialog::getOpenFileName(this,
												 tr("Open Image"), "", tr("JPEG Image Files (*.jpg)"));
	if(!fileName1.length()) return;
	auto file1 = StdStream::createReader(fileName1.toStdString());
	auto pic1 = Mh::ImageWrapper(*file1);
	if(!pic1.hasPixels()) throw std::runtime_error("Picture one is an invalid image!");
	auto fileName2 = QFileDialog::getOpenFileName(this,
												 tr("Open Image"), "", tr("JPEG Image Files (*.jpg)"));

	if(!fileName2.length()) return;
	auto file2 = StdStream::createReader(fileName2.toStdString());
	auto pic2 = Mh::ImageWrapper(*file2);
	if(!pic2.hasPixels()) throw std::runtime_error("Picture two is an invalid image!");
	if(pic1.getWidth() != pic2.getWidth() || pic1.getHeight() != pic2.getHeight())
		 throw std::runtime_error("Mismatch between the two pictures' dimensions!");
	pic1 = sharpnessComposite(pic1,pic2,15);
	if(!pic1.hasPixels()) throw std::runtime_error("Something went terribly wrong during the composition!");
	auto saveName = QFileDialog::getSaveFileName(this,
												 tr("Save Image"), "", tr("JPEG Image Files (*.jpg)"));
	if(!saveName.length()) return;
	auto saveUtf8 = saveName.toStdString();
	if(!pic1.save(Mh::ImageFileType::JPEG,saveUtf8.c_str()))
		throw std::runtime_error("Failed to save the image!");
	QMessageBox messageBox;
	messageBox.information(this,"Success!","Successfully saved the composite!");
	messageBox.setFixedSize(500,200);
	} catch(const std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(this,"Error",e.what());
		messageBox.setFixedSize(500,200);
	}
}

void MainWindow::on_editImg_clicked()
{
	try {
	auto fileName1 = QFileDialog::getOpenFileName(this,
													 tr("Open Image"), "", tr("JPEG Image Files (*.jpg)"));
	if(!fileName1.length()) return;
	auto file1 = StdStream::createReader(fileName1.toStdString());
	auto pic1 = Mh::ImageWrapper(*file1);
	ImageAdjuster adjust(std::move(pic1),this);
	adjust.setModal(true);
	adjust.exec();
	adjust.exec();
	} catch(const std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(this,"Error",e.what());
		messageBox.setFixedSize(500,200);
	}
}

void MainWindow::on_profileImage_clicked()
{
	try {
	auto fileName1 = QFileDialog::getOpenFileName(this,
													 tr("Open Image"), "", tr("JPEG Image Files (*.jpg)"));
	if(!fileName1.length()) return;
	auto file1 = StdStream::createReader(fileName1.toStdString());
	auto pic1 = Mh::ImageWrapper(*file1);
	ProfileDialog adjust(std::move(pic1),this);
	adjust.setModal(true);
	adjust.exec();
	adjust.exec();
	} catch(const std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(this,"Error",e.what());
		messageBox.setFixedSize(500,200);
	}
}
