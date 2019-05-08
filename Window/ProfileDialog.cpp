#include "ProfileDialog.hpp"
#include "ui_ProfileDialog.h"
#include "../ImgClassifier/ProfileImage.hpp"
#include <QFileDialog>
#include <QMessageBox>

ProfileDialog::ProfileDialog(Mh::ImageWrapper&& wrap, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ProfileDialog)
{
	Mh::ImageWrapper tmp = wrap;
	ui->setupUi(this);
	ui->AvgSharpness2->setReadOnly(true);
	ui->MinSharpness2->setReadOnly(true);
	ui->MaxSharpness2->setReadOnly(true);
	updateProfile(tmp);
	updateDisplay();
}

ProfileDialog::~ProfileDialog()
{
	delete ui;
}
void ProfileDialog::updateProfile(const Mh::ImageWrapper& wrap)
{
	preview = produceSharpnessProfile(wrap,15,&fmin,&fmax,&favg);
}
void ProfileDialog::updateDisplay()
{
	ui->AvgSharpness2->setText(QString::number(favg));
	ui->MinSharpness2->setText(QString::number(fmin));
	ui->MaxSharpness2->setText(QString::number(fmax));
	Mh::ImageWrapper tmp = preview.cloneAsStandardType();
	auto jpEgV = tmp.saveToMemory(Mh::ImageFileType::JPEG);
	image.loadFromData(reinterpret_cast<uchar*>(jpEgV.data()),jpEgV.size());
	ui->ImageProfile->setPixmap(image);
	ui->ImageProfile->setScaledContents(true);
}

void ProfileDialog::on_Discard_clicked()
{
	close();
}

void ProfileDialog::on_Save_clicked()
{
	try {
		Mh::ImageWrapper tmp = preview.cloneAsStandardType();
	auto saveName = QFileDialog::getSaveFileName(this,
		tr("Save Image"), "", tr("JPEG Image Files (*.jpg)"));
	if(!saveName.length()) return;
	auto saveUtf8 = saveName.toStdString();
	if(!preview.save(Mh::ImageFileType::PNG,saveUtf8.c_str()))
		throw std::runtime_error("Failed to save the image!");
	QMessageBox messageBox;
	messageBox.information(this,"Success!","Successfully saved the image!");
	messageBox.setFixedSize(500,200);
	} catch(const std::exception& e)
	{
		QMessageBox messageBox;
		messageBox.critical(this,"Error",e.what());
		messageBox.setFixedSize(500,200);
	}
	close();
}
